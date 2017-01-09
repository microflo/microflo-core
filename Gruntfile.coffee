
microflo = (target) ->
    build = [
        "make -f ./node_modules/microflo-emscripten/Makefile"
        target
        "BUILD_DIR=build/emscripten"
        "MICROFLO=./node_modules/.bin/microflo"
        "GRAPH=graph.fbp"
        "MICROFLO_SOURCE_DIR=`pwd`/node_modules/microflo/microflo"
        "PROJECT_DIR=`pwd`/node_modules/microflo-emscripten"
        "LIBRARY=`pwd`/components/arduino-standard.json"
    ]
    return build.join ' '

module.exports = ->
  # Project configuration
  @initConfig

    # lint
    coffeelint:
      code:
        files:
          src: ['lib/*.coffee', 'spec/*.coffee']
        options:
          max_line_length:
            value: 100
            level: 'warn'
          no_trailing_semicolons:
            level: 'warn'

    # TODO: Browser build

    exec:
        microflo_emscripten: microflo "build-emscripten"

    mochaTest:
      nodejs:
        src: ['spec/*.coffee']
        options:
          reporter: 'spec'
          require: 'coffee-script/register'
          grep: process.env.TESTS

  # Grunt plugins used for building
  @loadNpmTasks 'grunt-exec'

  # Grunt plugins used for testing
  @loadNpmTasks 'grunt-mocha-test'

  # Our local tasks
  @registerTask 'build', [
    'exec:microflo_emscripten'
  ]

  @registerTask 'test', [
    'build'
    'mochaTest'
  ]

  @registerTask 'default', ['test']

