<div align="center">
	
# HomeDicator
###### A customisable SenseCap Indicator Firmware using ESPHome. Design inspired by the [official example project](https://github.com/Seeed-Solution/SenseCAP_Indicator_ESP32/tree/main/examples/indicator_ha). 
	
</div>

<img src="./.assets/cover_image.jpg">


## Features
- Supports multiple pages
- Each page can have multiple tiles
	-	Currently supported tiles are: 
		- Sensor tiles (square & wide)
		- More will be added in the future
- Settings page to configure screen timeout, 24h clock and screen brightness

## Planed
- Additional tiles including:
	- Light brightness tiles
	- Thermostat tiles
	- Switch tiles
	- Button tiles
- Thermostat view (that can be linked to a tile showing the current temperature and opens on click)

## Configuration
Copy both the `sensecap-indicator.yaml` and the `sensecap-indicator` folder into your esphome config folder.  
You can have multiple `sensecap-indicator.yaml` with different names for different devices.  
The folder must retain its name and does not need to be duplicated for each device. 

Open the `sensecap-indicator.yaml` and get conformable with its settings.  
The following is an example of how to add a sensor to a page (the only functionality currently supported).

Below the sensor block, add the following configuration for each sensor you wish to add:
```
- !include 
    file: sensecap-indicator/core/templates/sensor.yaml
    vars:
      hass_sensor_id: "sensor.airgradient_schlafzimmer_temperature"
      esphome_sensor_id: "airgradiant_schlafzimmer_temp"
```
**hass\_sensor\_id:** This is the entity ID of your sensor in Home Assistant.  
**esphome\_sensor\_id:** This is the ID that the sensor will use within ESPHome. It can be freely set but must be unique.

Once you have added your sensors, go to the **ADD / ADJUST YOUR PAGES HERE** section.
A page looks like this:
```
- id: first_page
  bg_color: 0x1b1b1b # PAGE BACKGROUND COLOR
  bg_opa: COVER
  widgets:
    - !include
        file: sensecap-indicator/user_interface/templates/page_title.yaml
        vars:
          title: "Bedroom" # CHANGE PAGE TITLE HERE
    - obj:
        styles: content_container
        layout: 
          type: FLEX
          flex_flow: ROW_WRAP
          flex_align_main: LV_FLEX_ALIGN_START
          flex_align_cross: CENTER
          widgets:
            # Your tiles go here!
```
You can use this block if you want to add more pages. Make sure that the id is unique and that you update the title.  

To add a tile add the following block below `widgets:`.
```
- !include
    file: sensecap-indicator/user_interface/templates/tiles/sensor_tile.yaml
    vars:
      esphome_sensor_id: "airgradiant_schlafzimmer_temp"
      icon: "\U000F02E3"
      unit: "°C"
      subtitle: "Bedroom"
```	
You can change `sensor_tile.yaml` to `sensor_tile_wide.yaml` for a tile version that is wide instead of square.  

**esphome\_sensor\_id:** Must match with the ID you used to add the sensor in the beginning.  
**icon:** Unicode codepoint of the icon you want to use. See [here](https://github.com/paviro/HomeDicator/blob/main/ESPHome/sensecap-indicator/core/fonts.yaml) for icons that are available.  
**unit:** Unit of the sensor.  
**subtitle:** Subtitle shown below the sensor value.

A screen can hold four square tiles at a time, but you can add more and access them by scrolling down on the Indicator.  

When you have finished adding pages, update the `total_pages` variable at the top of the file to reflect your total pages + the settings page.  

Make sure to add your device to Home Assistant (it should be discovered automatically) as it will not receive data if you don't.

## A word of caution!
I build this in my spare time as a hobby.  
In general, I make no guarantees that it will work forever, even though I intend to keep maintaining it, but sometimes other things are more important.  
**I also give no guarantees that updates here will not break existing configurations and require a new configuration - especially now in the early stages this will definitely happen!**