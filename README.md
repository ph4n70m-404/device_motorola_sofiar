# Sofiar
This repository is the device tree for Sofiar.  
This readme will be used for general information on the roms I build for Sofiar.

# Reporting Issues
You can report issues [here](https://github.com/ph4n70m-404/device_motorola_sofiar-1/issues).  
Be sure to include the name of the rom you are reporting an issue for.

# Sofiar Trees
**Device Tree:**  
[device_motorola_sofiar](https://github.com/ph4n70m-404/device_motorola_sofiar-1)  
**Vendor Tree:**  
[vendor_motorola_sofiar](https://github.com/ph4n70m-404/vendor_motorola_sofiar)  
**Samuel's Kernel:**  
[kernel_motorola_trinket](https://github.com/S4muel007/kernel_motorola_trinket)

# Havoc Sofiar Trees
**Device Tree:**  
[android_device_motorola_sofiar](https://github.com/Havoc-Devices/android_device_motorola_sofiar)  
**Vendor Tree:**  
[android_vendor_motorola_sofiar](https://github.com/Havoc-Devices/android_vendor_motorola_sofiar)  
**Samuel's Kernel:**  
[android_kernel_motorola_trinket](https://github.com/Havoc-Devices/android_kernel_motorola_trinket) 

# Rom Downloads
[Lineage OS builds](https://www.androidfilehost.com/?w=files&flid=328626)  
[Miscellaneous/Defunct Builds](https://androidfilehost.com/?w=files&flid=329294)

# How to adapt this tree to your needs.
**(I would recommend you create a fork and do the edits there so that if you need help you can show the device tree to other people and pull any new commits i make to the new tree easily.)**  
1. First off rename every instance of the word ROM to the roms name or what they internally call themselves, for example Potato Open Sauce Project shortens to potato.  
2. Then you are going to want to look at the manifest page for rom specific instructions and follow those. (You can also generally find what they call themselves internally here.)  
3. Then you want to adapt [this gerrit](https://gerrit.omnirom.org/c/android_frameworks_base/+/39046) to the rom manually if they haven't already pulled it into the source. 
4. Make sure the rom doesn't have [this line](https://github.com/LineageOS/android_device_lineage_sepolicy/blob/9f177f7b3a96573712652320d3ec8ebdfcda946a/common/dynamic/hwservice_contexts#L1).
5. Then add [Moto Camera](https://gitlab.com/NemesisDevelopers/moto-camera/motorola_camera2_logan) and [Moto Widget](https://gitlab.com/NemesisDevelopers/motorola/motorola_timeweather). (Just the git clone commands.)
6. Make sure you have already downloaded the [kernel](https://github.com/S4muel007/kernel_motorola_trinket) and [vendor tree](https://github.com/ph4n70m-404/vendor_motorola_sofiar).
7. Then you want to do a build to make sure everything builds and debug any errors you get.  
8. After the build you should run "development/tools/privapp_permissions/privapp_permissions.py" to make sure you arent missing any permissions.  
9. Finally if you are missing any permission add them into the device tree under the permissions folder and rebuild.  

**(If you need any help feel free to ask for it on the telegram)**  
