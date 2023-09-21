








/****************************
* @brief f_SimpleFilter
* Basic filter functionality without all the bells and whistles.
* NOTE: Doesn't use any data saved etc.
*
* Simply performs a mathematical floating point filter based upon old sample value, new sample value,
* the amount of real time that has elapsed between samples and a filter 'Time', which represents the
* real world time a signal would take to change from 10% to 90% of a step change.
* Essentially a low-pass filter - the higher the 'FilterTime' the smoother the results (but less responsive of course!).
* An alternative shifting integer filter could be used for faster / lower resolution (simple) filtering... if needed.
*
* @param float newValue - parameters as described above.
* @param float oldValue - previous value returned by this function.
* @param uint64_t mSSinceUpdate - mS Since the last update.
* @param uint64_t FilterTime_mS - Filter "Time Period" - the time it would take for a transition of 90% of the change.
*
* @retval float: Filtered value.
*/
float f_SimpleFilter(float newValue, float oldValue, uint64_t mSSinceUpdate, uint64_t FilterTime_mS)
{
	// Trap too long since update to filter properly.
	if (mSSinceUpdate < FilterTime_mS)
		// Return filtered value
		return oldValue + ((newValue - oldValue) * ((float)mSSinceUpdate / (float)FilterTime_mS));
	else
		// Reset to current value. Too much time has elapsed to properly filter anything!
		return newValue;
}





/****************************
* @brief ul_Digit_Count
* Counts number of digits in a number.
* @param Number to count digits of
* @retval unsigned char: Number of digits found.
*/
unsigned char ul_Digit_Count(unsigned long ul_Value)
{
	unsigned char uc_Count = 0;
	while(ul_Value)
	{
		uc_Count++;
		ul_Value /= 10;
	}
	return uc_Count;
}
