chai = require 'chai'
microflo = require 'microflo'
comps = require '../build/emscripten/componentlib-map.json'
build = require '../build/emscripten/microflo-runtime.js'

fs = require 'fs'
path = require 'path'

subscribeOutports = (rt, callback) ->
    edges = []
    outports = rt.graph.outports
    for exported, internal of outports
        edges.push
            src:
                process: internal.process
                port: internal.port
    microflo.runtime.subscribeEdges rt, edges, callback

# Mocha runner
testSubject = (subject, tests) ->
    prog = tests.fixture.data

    describe "#{subject}", ->
        simulator = new microflo.simulator.RuntimeSimulator build
        onReceived = null
        beforeEach (done) ->
            onReceived = (port, type, data) ->
                throw new Error 'onReceived not set'
            simulator.library.definition = comps
            simulator.start 0 # no time increments
            simulator.device.on 'response', () ->
                event = arguments[0]
                if event == 'SEND'
                    # TODO: map back from internal to exported port names
                    [e, node, port, type, data] = arguments
                    onReceived port, type, data
                else if event == 'ERROR'
                    args = Array.prototype.slice.call arguments
                    done new Error args.join ', '
            simulator.device.open (err) ->
                chai.expect(err).to.not.exist
                simulator.uploadFBP prog, (err) ->
                    chai.expect(err).to.not.exist
                    subscribeOutports simulator, (err) ->
                        chai.expect(err).to.not.exist
                        done()
        afterEach (done) ->
            simulator.device.removeAllListeners 'response'
            simulator.device.close ->
                simulator.stop()
                done()

        tests.cases.forEach (tcase) ->
            describe tcase.name, ->
                it tcase.assert, (done) ->
                    # listen outputs, verify against expected
                    received = {}
                    bracketed = null
                    onReceived = (port, type, data) ->
                        # FIXME: move this bracket handling into MicroFlo core somewhere
                        if bracketed? and type != 'BracketEnd'
                            bracketed.push data
                            return
                        if type == 'BracketStart'
                            bracketed = []
                            return
                        if type == 'BracketEnd'
                            data = bracketed.slice()
                            bracketed = null
                        received[port] = data
                        nExpected = Object.keys(tcase.expect).length
                        if Object.keys(received).length == nExpected
                            # something is catching our exceptions =\
                            error = null
                            try
                                chai.expect(received).to.eql tcase.expect
                            catch e
                                error = e
                            done error
                    # send input packets
                    microflo.runtime.sendPackets simulator, tcase.inputs, (err) ->
                        chai.expect(err).to.not.exist

listComponents = (dir) ->
    library = new microflo.componentlib.ComponentLibrary
    filenames = fs.readdirSync dir
    for filename in filenames
        filepath = path.join dir, filename
        library.loadFile filepath
    components = library.listComponents()
    return components

findComponentTests = (testsDir, componentName) ->
    testPath = path.join testsDir, componentName+'.yaml'
    console.log testPath
    try
        contents = fs.readFileSync testPath
    catch e
        return null
    try
        tests = require('js-yaml').safeLoad contents
    catch e
        console.log "Could not load tests for #{componentName}", e
        return null
    return tests

main = () ->
    testsDir = './spec'
    components = listComponents './components'
    components.forEach (componentName) ->
        tests = findComponentTests testsDir, componentName
        if not tests or not tests.cases.length
            describe "#{componentName}", () ->
                it.skip 'should have tests'
        else
            testSubject componentName, tests

main()
