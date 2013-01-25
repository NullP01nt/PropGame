#!/bin/bash

echo $(propeller-elf-readelf -S include/sd_cache_menu.elf | grep .coguser1)
