# THIS REPO IS WORK IN PROGRESS
# rosserial_stm32

## Note
This is a part of [rosserial](https://github.com/ros-drivers/rosserial) repository to communicate with ROS system through a USART for STM32 embedded system.

## Limitation
The original code is focused on STM32F3xx, 4xx, and 7xx series and it uses the [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) or [STM32CubeMX HAL](http://www.st.com/en/development-tools/stm32cubemx.html).  
If you use the package for other series, please edit [the following line](https://github.com/yoneken/rosserial_stm32/blob/master/src/ros_lib/STM32Hardware.h#L38) on src/ros_lib/STM32Hardware.h with corresponding HAL library. 
It may happen code will work even with HAL library for other STM32 processor family. 
**If you run into troubles, please check src/ros_lib/STM32Hardware.h first**



## Generate code
$ cd _target_workspace_ (It should contain Inc and Src directories).  
$ rosrun rosserial_stm32 make_libraries.py .  
**Never forget to change the project type to _cpp project_ in STM32CubeIDE**  

### Set up in STM32CubeIDE

1. Generate headers for STM32 (use [rosserial_client](http://wiki.ros.org/rosserial_client) or [rosserial_arduino](http://wiki.ros.org/rosserial_arduino))
2. Paste all generated header files into `Core/Inc` directory
3. Copy files `ros.h` and `STM32Hardware.h` to `Core/Inc`
4. In your `.ioc` file under `connectivity` and select `UART2` accordingly to the examplar file `g031_rosserial.ioc`
5. Make sure your code implements iterrupt function void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) same as in examplar file `main.cpp`
   
