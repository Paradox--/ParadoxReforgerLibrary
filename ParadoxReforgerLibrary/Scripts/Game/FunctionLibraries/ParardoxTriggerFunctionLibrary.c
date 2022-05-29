



//------------------------------------------------------------------
// Trigger Helper Library 											-
// All methods here are related to the trigger functions.  		-
//------------------------------------------------------------------
class ParadoxTriggerFunctionLibrary
{
	// -- Runtime Properties -- // 
	
	// a runtime pointer for the runtime manager, this is created and 
	// and destroyed as needed.  
	static ParadoxTriggerManagerBase runtimeManagerPtr = null; 
	
	// -- Manager Methods -- // 
	
	// returns if there is a valid function library manager pointer.
	static bool HasTriggerManager()
	{
		return runtimeManagerPtr != null; 
	}
	
	// returns the current runtime trigger manager pointer. 
	static ParadoxTriggerManagerBase GetTriggerManager()
	{
		return runtimeManagerPtr; 
	}
	
	static bool FindBasicTriggerInstanceWithTag(string tagToFind, out SCR_ParadoxTriggerBase foundTrigger)
	{
		// if the trigger manager is null. 
		if(!HasTriggerManager())
		{
			// null out the trigger, and return false; 
			foundTrigger = null; 
			return false; 
		}	
		else // else ... 
		{
			return GetTriggerManager().FindBasicTriggerInstanceWithTag(tagToFind, foundTrigger); 
		}
	}
	
	// returns if we were able to find any faction triggers with a specific tag. If there are more 
	// triggers with that tag, we return the first element in the list. 
	static bool FindFactionTriggerInstanceWithTag(string tagToFind, out SCR_ParadoxFactionTrigger foundTrigger)
	{
		// if the trigger manager is null. 
		if(!HasTriggerManager())
		{
			// null out the trigger, and return false; 
			foundTrigger = null; 
			return false; 
		}	
		else // else ... 
		{
			return GetTriggerManager().FindFactionTriggerInstanceWithTag(tagToFind, foundTrigger); 
		}
	}
	
	// returns if we could get a copy list from the master list. 
	static bool FindBasicTriggerListWithTag(string tagToFind, out array<SCR_ParadoxTriggerBase> foundTriggers)
	{
		// if the trigger manager is null. 
		if(!HasTriggerManager())
		{
			// null out the trigger list, and return false; 
			foundTriggers = new array<SCR_ParadoxTriggerBase>(); 
			return false; 
		}	
		else // else ... 
		{
			return GetTriggerManager().FindBasicTriggerListWithTag(tagToFind, foundTriggers); 
		}
	}
	
	// returns if we could get a copy list from the master list. 
	static bool FindFactionTriggerListWithTag(string tagToFind, out array<SCR_ParadoxFactionTrigger> foundTriggers)
	{
		// if the trigger manager is null. 
		if(!HasTriggerManager())
		{
			// null out the trigger list, and return false; 
			foundTriggers = new array<SCR_ParadoxFactionTrigger>(); 
			return false; 
		}	
		else // else ... 
		{
			return GetTriggerManager().FindFactionTriggerListWithTag(tagToFind, foundTriggers); 
		}
	}
	
	// returns if we were able to add a trigger with a specific tag. 
	static bool AddBasicTriggerWithTag(SCR_ParadoxTriggerBase triggerToAdd)
	{
		// if the trigger manager is null. 
		if(!HasTriggerManager())
		{
			return false; 
		}	
		else // else ... 
		{
			return GetTriggerManager().AddBasicTriggerWithTag(triggerToAdd); 
		}
	}
	
	// returns if we are able to add a faction trigger with its tag. 
	static bool AddFactionTriggerWithTag(SCR_ParadoxFactionTrigger triggerToAdd)
	{
		// if the trigger manager is null. 
		if(!HasTriggerManager())
		{
			return false; 
		}	
		else // else ... 
		{
			return GetTriggerManager().AddFactionTriggerWithTag(triggerToAdd); 
		}
	}
	
	static bool RemoveBasicTriggerWithTag(SCR_ParadoxTriggerBase triggerToRemove)
	{
		// if the trigger manager is null. 
		if(!HasTriggerManager())
		{
			return false; 
		}	
		else // else ... 
		{
			return GetTriggerManager().RemoveBasicTriggerWithTag(triggerToRemove); 
		}	
	}
	
	static bool RemoveFactionTriggerWithTag(SCR_ParadoxFactionTrigger triggerToRemove)
	{
		// if the trigger manager is null. 
		if(!HasTriggerManager())
		{
			return false; 
		}	
		else // else ... 
		{
			return GetTriggerManager().RemoveFactionTriggerWithTag(triggerToRemove); 
		}		
	}
	
	
	// seed the trigger manager pointer. This is set by an instance of the Paradox trigger manager. 
	static void CreateTriggerManager(ParadoxTriggerManagerBase newManager)
	{
		// if we already have a manager... 
		if(HasTriggerManager())
		{
			// bail out... 
			return; 
		}
		else // else ... 
		{
			// save the runtime ptr. 
			runtimeManagerPtr = newManager;
		}
	}
	
	// cleans up the current trigger manager pointer. 
	static void DestroyTriggerManager(ParadoxTriggerManagerBase managerToRemove)
	{
		// if we do not have a runtime pointer, or this isnt our runtime global pointer.  
		if(!HasTriggerManager() || (GetTriggerManager() != managerToRemove))
		{
			// bail out... 
			return; 
		}
		else // else .. 
		{
			// remove that pointer. 
			runtimeManagerPtr = null;
		}
	}
};