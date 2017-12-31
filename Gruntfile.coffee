
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
        fbpspec: "./node_modules/.bin/fbp-spec --address ws://localhost:3333 --command 'sh spec/start-runtime.sh' --start-timeout 20 spec/"

  # Grunt plugins used for building
  @loadNpmTasks 'grunt-exec'

  # Our local tasks
  @registerTask 'build', [
    'exec:build_runtime'
  ]

  @registerTask 'test', [ 'build', 'exec:fbpspec' ]
  @registerTask 'default', ['test']

