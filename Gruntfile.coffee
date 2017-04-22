
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

    exec:
        build_runtime: "make runtime"
        update_components: "make components"

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
    'exec:update_components'
    'exec:build_runtime'
  ]

  @registerTask 'test', [
    'build'
    'mochaTest'
  ]

  @registerTask 'default', ['test']

