
cases = [
  name: 'no-animation-setup'
  assert: 'should-give-false'
  inputs:
    clock: 100
  expect:
    value: false
    running: false
,
  name: 'in-first-period-high'
  assert: 'should-give-true'
  inputs:
    start: 1000
    duration: 200
    period: 200
    clock: 1050
  expect:
    value: true
    running: true
,
  name: 'in-first-period-low'
  assert: 'should-give-false'
  inputs:
    start: 1000
    duration: 400
    period: 200
    clock: 1150
  expect:
    value: false
    running: true
,
  name: 'before-animation-start'
  assert: 'should-give-false'
  inputs:
    start: 100
    duration: 100
    clock: 99
  expect:
    value: false
    running: false
,
  name: 'after-animation-end'
  assert: 'should-give-false'
  inputs:
    start: 101
    duration: 200
    clock: 302
  expect:
    value: false
    running: false
]
component = "ToggleAnimation" # should implitly create graph?
prog = """
# @runtime microflo

INPORT=it.CLOCK:CLOCK
INPORT=it.VALUE0:VALUE0
INPORT=it.VALUE1:VALUE1
INPORT=it.START:START
INPORT=it.PERIOD:PERIOD
INPORT=it.DURATION:DURATION
INPORT=it.DUTYCYCLE:DUTYCYCLE
OUTPORT=it.RUNNING:RUNNING
OUTPORT=it.VALUE:VALUE

it(ToggleAnimation) VALUE -> IN v(Forward)
it RUNNING -> IN r(Forward)
"""

chai = require 'chai'
microflo = require 'microflo'
comps = require '../build/emscripten/componentlib-map.json'
build = require '../build/emscripten/microflo-runtime.js'

subscribeOutports = (rt, callback) ->
    edges = []
    outports = rt.graph.outports
    for exported, internal of outports
        edges.push
            src:
                process: internal.process
                port: internal.port
    microflo.runtime.subscribeEdges rt, edges, callback

describe "#{component}", ->
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

    cases.forEach (tcase) ->
        describe tcase.name, ->
            it tcase.assert, (done) ->
                # listen outputs, verify against expected
                received = {}
                onReceived = (port, type, data) ->
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
