# ESP32 HTTP Get Set

A small, simple example to to create HTTP endpoints allowing you to get and set values on an ESP32/Arduino device. 

I use an edited version of this to control the LED light strips in my room. With this, I don't need to have separate webpages for each of my ESP32 devices. Instead, I can control them from a single webpage that just runs its own HTTP GET/POST requests.

This is **not** a library, but an example to build off of. 

## Usage

1. Download and open the code 
2. Install the prerequisite libraries specified at the top
3. Update the WIFI SSID and password
4. Configure the default values in `configureJsonDocument`. These will be the values at device turn-on. If you wish to restore the state from memory, this is where to do so.
5. Compile and run on your ESP32/Arduino device

Once running, two HTTP endpoints will be created. 

- `/get` GET will return a JSON object of the current state of the current values 
- `/set?field=<field_name>&value=<value>` POST will set the value of a field to the provided value

For example, my LED lights operate like so:

- GET request `/get` to check the status of the lights. If it's on, display an off switch, etc.
- POST `/set?field=active&value=true` to set the `active` flag to `true` when switch is toggled ON
- POST `/set?field=active&value=false` to set the `active` flag to `false` when switch is toggled OFF
- Once per second, the ESP32/Arduino polls (in the `loop` function) to update state of the lights (e.g. by powering on/off the pins to the relay).