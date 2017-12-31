
# microflo-core

## 0.6.0 - released N/A

Breaking changes

* Components moved to `microflo-arduino`:
LedChainNeoPixel, LedChainWS, LedMatrixMax, ReadDallasTemperature, UltrasoundSR04, MonitorPin
* Components moved to `microflo-contrib`:
ArduinoUno, BreakBeforeMake, MbedLPC, ToggleAnimation, ToggleAnimationsN

Improvements

* All components now specify datatypes on ports 

## 0.5.0 - released 30.12.2017

Breaking changes

* Requires MicroFlo 0.5.0+
* Removed several unused/not-useful components: `SerialIn`, `SerialOut`, `Delimit`, `ATUSBKEY`, `TivaC`
* Several components that used to send on network start now has mandatory triggering ports:
`MbedLPC`, `ArduinoUno`

Internal changes

* Added more type annotations on ports
* Added more tests

## 0.3.38 - released 10.05.2017

Internal changes

* Using Linux as the primary backend for test, versus Emscripten before

## 0.3.*

## 0.3.23 - released 21.03.2015

First release

* Split out of main `microflo` repository
