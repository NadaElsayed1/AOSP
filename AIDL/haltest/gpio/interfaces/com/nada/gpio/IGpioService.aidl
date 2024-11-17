
package com.nada.gpio;

interface IGpioService {
	boolean setGpioState(int pin, boolean value);
	boolean getGpioState(int pin);
}
