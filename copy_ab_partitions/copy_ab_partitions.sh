#!/system/bin/sh

#####################################################
# Flashize Runtime (2016-04-06)                     #
# Copyright 2016, Lanchon                           #
#####################################################

#####################################################
# The Flashize Runtime is free software licensed    #
# under GNU's Lesser General Public License (LGPL)  #
# version 3 and any later version.                  #
# ------------------------------------------------- #
# Note: The code appended to the Flashize Runtime,  #
# if any, is independently licensed.                #
#####################################################

suffix_active=$(getprop ro.boot.slot_suffix)
recovery_running=$(getprop init.svc.recovery)

echo "running post install copy_ab_partitions"

if [[ "$recovery_running" != "running" ]]; then
    echo "not in recovery, exiting"
    exit 0
fi

# Partitions ignored
IGNORED="dtbo_a dtbo_b system_a system_b boot_a boot_b product_a product_b vbmeta_a vbmeta_b vendor_a vendor_b"

echo "current slot ${suffix_active}"

if [[ "$suffix_active" == "_a" ]]; then
  suffix_swap="_b"
else
  echo "no need to copy partitions to slot _a, exiting"
  exit 0
fi

for active in /dev/block/bootdevice/by-name/*$suffix_active; do
	partition=$(basename $active)
    if [[ "${IGNORED/$partition}" = "$IGNORED" ]]; then
        echo "Partition $partition"
  	    inactive=$(echo $active | sed "s/${suffix_active}\$/${suffix_swap}/");
        part_active=$(readlink -fn $active);
        part_inactive=$(readlink -fn $inactive);
        if [[ -n "$part_active" && -n "$part_active" && "$active" != "$part_active" && "$inactive" != "$part_inactive" ]]; then
          dd if=$part_active of=$part_inactive
        fi
    fi
done

exit 0

