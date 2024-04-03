// Task: implement a program with external interrupt mechanism, that will use two buttons: first one will increment a value, the second one (after two sequential presses) will blink the LED as many times as was stored in the value.

// Exempt from main.c showcasing the solution:

/* USER CODE BEGIN PV */
uint8_t PC13_flag = 0;
uint8_t PA5_flag = 0;
uint8_t BLINK_flag = 0;
/* USER CODE END PV */

/* USER CODE BEGIN 0 */
void LED_RESET() {
	HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_RESET);
}
void OUTPUT_NUM(uint8_t num) {
	LED_RESET();
	switch (num) {
	  case 1:
		  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_SET);
		  break;
	  case 2:
		  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
		  break;
	  case 3:
		  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
		  break;
	  case 4:
		  HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_SET);
		  break;
	  case 5:
		  HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_SET);
		  break;
	  case 6:
		  HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
		  break;
	  case 7:
		  HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_SET);
		  break;
	  default:
		  break;
	  }
}
/* USER CODE END 0 */


while (1)
 {
   /* USER CODE END WHILE */
    if (BLINK_flag) {
        if (PC13_flag <= 0) {
            PC13_flag = 0;
            BLINK_flag = 0;
            OUTPUT_NUM(PC13_flag);
        }
        else {
            OUTPUT_NUM(PC13_flag);
            HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, GPIO_PIN_SET);
            HAL_Delay(200);
            HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, GPIO_PIN_RESET);
            HAL_Delay(200);
            PC13_flag--;
        }
    }
   /* USER CODE BEGIN 3 */
 }


/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == USER_EXTI_Pin) {
		PC13_flag++;
        PA5_flag = 0;
	}
	else if (GPIO_Pin == BTN_EXTI_Pin) {
		PA5_flag++;
		if (PA5_flag >= 2) {
			BLINK_flag = 1;
			PA5_flag = 0;
		}
	}
	if (PC13_flag > 7) {
		PC13_flag = 0;
	}
	OUTPUT_NUM(PC13_flag);
}
/* USER CODE END 4 */


// Explanation of the solution:
// We have two flags to keep track of the number of times the buttons have been pressed. PC13 flag keeps track of the user button, the PA5 flag - of the external button. Both buttons are set up as rising edge external interrupts. When the user button is pressed, we just add 1 to its flag (PC13), and output the current value of the flag with LEDs. We also make sure that the value is cyclic and stays below 7 - after 7 we go to 0. Now, whenever the other external button is pressed twice in a row - we activate the blinking by setting the BLINK flag. This in order triggers the if statement in the main while loop, that runs the blinking logic of LED - LED will blink the amount of times set by the PC13 flag. The PC13 flag itself will dynamically decrease which we will see with the other three LEDs. Finally, after the PC13 flag is depleted, we set the BLINK flag back to 0, and the program returns to the initial state.
