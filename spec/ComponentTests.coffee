fbpspec = require 'fbp-spec'
runtime = require './simulator.json'

fbpspec.mocha.run runtime, __dirname, { starttimeout: 10*1000 }
