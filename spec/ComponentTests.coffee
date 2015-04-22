fbpspec = require 'fbp-spec'
runtime = require './simulator.json'

fbpspec.mocha.run runtime, __dirname, {}
