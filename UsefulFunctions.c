/******************************************************************
* This file is to be used to make edits, cause conflicts and then
* resolve them through pull request, resolve conflicts and merging.
* 
* Step 1: Clone this repo to your local machine. You'll also need to notify me
* that you want to be a collaborator for this repo (please remind me of your GitHub user name).
*
* Step 2: Create a branch that you'll be committing your changes to.
* Note: It might be worth including your name in the branch name as we
* may well end up with many many branches! i.e. Mine would be "Dev_Steve"
* 
* Step 3: Make and commit changes...
* There are three functions at the top of this file (below), each with
* instructions to edit in a certain way.
* 
* Step 4: Create a Pull Request and add support@yourengineeringsuccess.co.uk as a reviewer.
* 
* Step 5: Wait. I'll need to receive the pull request, then modify the main/master branch in
* the relevant way to cause the intended type of conflict with your merge.
* I'll add a comment to the pull request when this is done (you'll also see the display will change
* to indicate there are conflicts that must be resolved before the merge can be completed).
*
* Step 6: Merge the master changes into your branch and resolve the conflicts there.
* 
* Step 7: Once conflicts are resolved request a final review before merging changes once approved.
* 
* IMPORTANT: With multiple people modifying the same lines of code on multiple branches the 
* conflict resolution may be a little complex at times, however this is the intended 'practice'
* we'll get from this.
* 
* -----
* Note: There's also a couple of "Helper" functions added at the bottom of this file,
* please feel free to add to these if you wish. 
* 
*/


/****************************
* @brief KeepBothChanges
* Changes to this function on both the master AND any development branch
* must ALL be kept when it comes to resolving conflicts.
*
* This represents the scenario where the main/master has been updated while you've
* been developing, and you need to include the new changes in main/master as well
* as the changes from your branch.
*/
void KeepBothChanges ( void )
{
	// Simply add a new line comment (like this one) below.
	// This is a line added for testing on Dev_YourName - Demo video.
	// This is a line added for testing on Dev_YourName - Demo video Take 2.
	// This is a line added to main that will conflict with other changes here.
}

/****************************
* @brief KeepMasterChangesDiscardDev( void )
* Changes to this function from main/master should be kept and the changes on your
* development branch should be discarded when it comes to resolving conflicts.
*
* This represents the scenario where the main/master has been updated in the same way
* that you've modified your development branch, in which case you want to keep the
* main/master changes and discard the same functionality you've added to your dev branch.
* After all, there's no point in making unnecessary changes.
*/
void KeepMasterChangesDiscardDev ( void )
{
	// Simply add a new line comment line below.
	// This is a line added for testing on Dev_YourName - Demo video.
	// This is a line added to main that will conflict with other changes here.
}

/****************************
* @brief KeepDevChangesOverrideMaster( void )
* Changes to this function from main/master should be discarded in favor of the changes
* on your development branch when it comes to resolving conflicts.
*
* This represents the scenario where the main/master has been updated in the same way
* that you've modified your development branch, however your development branch includes
* additional changes that are also now required.
*/
void KeepDevChangesOverrideMaster ( void )
{
	// Simply add a new line comment line below.
	// This is a line added for testing on Dev_YourName - Demo video.
	// This is a line added for testing on Dev_YourName - Demo video Take 2.
}




***********************************
***********************************
***********************************
***                             ***
*** HELPER FUNCTIONS BELOW HERE ***
***                             ***
***********************************
***********************************
***********************************







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
