// Task: implement conditional LED behaviour based on time passed, without using a timer or an interrupt mechanism.
// When the button is just pressed, toggle the LED. When the button is held for longer than 5 seconds, start blinking the LED.

// Exempt from main.c showcasing the solution:

// Global variables
uint8_t counter = 0;

// The main while loop
while (1)
 {
   /* USER CODE END WHILE */
	  if (HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin) == 1) {
		  HAL_Delay(100);
		  counter++;
		  if (HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin) == 1) {
			  while (HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin) == 1 && counter < 50) {
				  HAL_Delay(100);
				  counter++;
			  }
			  if (counter < 50) {
				  HAL_GPIO_TogglePin(YELLOW_GPIO_Port, YELLOW_Pin);
			  }
			  else {
				  while (HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin) == 1) {
					  HAL_Delay(100);
					  HAL_GPIO_TogglePin(YELLOW_GPIO_Port, YELLOW_Pin);
				  }
			  }
			  counter = 0;
		  }
	  }
   /* USER CODE BEGIN 3 */
 }

// Explanation of the solution:
// We use the counter value as the timer basically - I have set one division of a counter to be equal to 100 ms. That’s why in the debounce statement, after the debounce delay I increment the counter - you can say that I synchronized the counter variable with the time passed. Using this fact, I can write logic that checks whether a certain amount of time has passed, and do something. In my code, after the debounce statement, I have an inner while loop, that just busy waits (does nothing) while two conditions are being met - less than 5 seconds have passed (counter < 50), and the button is being kept pressed. If either of those conditions is broken, we do a certain action.
// If the button is released before 5 seconds, we enter the if statement after the while loop, which just toggles the LED.
// If however, the counter has reached 50 (50*100 = 5000 ms or 5 seconds have passed), it implies that the button is still being kept pressed, and thus we enter the else statement, where we have yet another while loop - while the button is kept pressed, blink the LED.
// At the end of all statements, we have a counter = 0, to start the program over.