/*
 * main.cpp

 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_conf.h"
#include <mainpp.h>
#include <ros.h>
#include <std_msgs/Byte.h>

extern TIM_HandleTypeDef htim1;
//extern TIM_HandleTypeDef htim2;
//extern UART_HandleTypeDef huart2;

ros::NodeHandle nh;
TIM_OC_InitTypeDef sConfigOC = {0};

void led0_cb(const std_msgs::Byte& msg);
void led1_cb(const std_msgs::Byte& msg);
void led2_cb(const std_msgs::Byte& msg);
void led3_cb(const std_msgs::Byte& msg);

std_msgs::Byte led0_val;
ros::Subscriber<std_msgs::Byte> led0_sub("led0", &led0_cb);
std_msgs::Byte led1_val;
ros::Subscriber<std_msgs::Byte> led1_sub("led1", &led1_cb);
std_msgs::Byte led2_val;
ros::Subscriber<std_msgs::Byte> led2_sub("led2", &led2_cb);
std_msgs::Byte led3_val;
ros::Subscriber<std_msgs::Byte> led3_sub("led3", &led3_cb);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void setup(void)
{
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

  nh.initNode();
  nh.subscribe(led0_sub);
  nh.subscribe(led1_sub);
  nh.subscribe(led2_sub);
  nh.subscribe(led3_sub);

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
}

void loop(void)
{
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

  nh.spinOnce();

  HAL_Delay(1000);
}

void led0_cb(const std_msgs::Byte& msg){
  sConfigOC.Pulse = msg.data;
  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
}

void led1_cb(const std_msgs::Byte& msg){
  sConfigOC.Pulse = msg.data;
  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
}

void led2_cb(const std_msgs::Byte& msg){
  sConfigOC.Pulse = msg.data;
  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
}

void led3_cb(const std_msgs::Byte& msg){
  sConfigOC.Pulse = msg.data;
  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);
}
