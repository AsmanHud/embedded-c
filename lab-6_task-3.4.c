// Task: translate a uint8_t variable into LEDs state (show the integer as a binary by lighting specific LEDs).
// Implementation is based on counting up, next state is dependant on the previous.

// Exempt from main.c showcasing the solution:

// Global variables
uint8_t counter = 0;

// Custom functions
void LED_RESET() {
	HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_RESET);
}

// Main while loop
while (1)
 {
   /* USER CODE END WHILE */
	  if (HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin) == 1) {
		  HAL_Delay(300);
		  if (HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin) == 1) {
			  counter++;
			  if (counter > 7) {
				  counter = 0;
			  }
			  if (counter <= 7) {
				  switch (counter) {
				  case 0:
					  LED_RESET();
					  break;
				  case 1:
					  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_SET);
					  break;
				  case 2:
					  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_RESET);
					  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
					  break;
				  case 3:
					  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_SET);
					  break;
				  case 4:
					  LED_RESET();
					  HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_SET);
					  break;
				  case 5:
					  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_SET);
					  break;
				  case 6:
					  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_RESET);
					  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
					  break;
				  case 7:
					  HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, GPIO_PIN_SET);
					  break;
				  default:
					  break;
				  }
			  }
		  }
	  }
   /* USER CODE BEGIN 3 */
 }

// Explanation of the solution:
// We have a custom function written to reduce the number of lines - LED_RESET. It’s simple - it just resets all the specified LEDs. We also have a global counter to keep track of which number to display. Speaking of the number - we use a switch statement to display a specific number using LEDs. The logic to turn on and off specific LEDs is sequential in my code - meaning each number can be displayed correctly only if it goes from 0 to 7 in order. While I don’t think I need to explain much each switch case in particular, here is some explanation:
// In case 0 (at the beginning, or when the counter gets larger than 7 and the first if statement after the counter++ sets it to 0), we just reset all LEDs.
// Then from 0 till 7, we turn and off specific LEDs like I mentioned, to translate the counter value to LEDs’ state.
// The first if statement after the counter++ always checks so that the counter value stays below or equal to 7. We thus can omit the default case.
