// This is a basic trigger manager, contains list of triggers such that we can get access to them from a function library. 
// -- Paradox


[EntityEditorProps(category: "ParadoxReforgerLibrary/Entities/Managers", description: "A basic trigger manager class. Holds references to triggers in the level.")]
class ParadoxTriggerManagerBaseClass: GenericEntityClass
{
};

class ParadoxTriggerManagerBase: GenericEntity
{
	// -- Class Properties -- // 
	
	// A running list of basic triggers. 
	protected ref map<string, ref array<SCR_ParadoxTriggerBase>> BasicTriggerMap = new ref map<string, ref array<SCR_ParadoxTriggerBase>>;
	
	// a running list of faction triggers. 
	protected ref map<string, ref array<SCR_ParadoxFactionTrigger>> FactionTriggerMap = new ref map<string, ref array<SCR_ParadoxFactionTrigger>>;
	
	// -- Constructor / Destructor -- // 
	void ~ParadoxTriggerManagerBase()
	{
		// nuke our data containers.. 
		BasicTriggerMap.Clear(); 
		FactionTriggerMap.Clear();
		
		// nuke the poiner if we set it. 
		// @TODO: Ask for a DEINIT method to move this too. 
		// THIS IS SUPER DIRTY TO PUT IT IN THE DESTRUCTOR
		ParadoxTriggerFunctionLibrary.DestroyTriggerManager(this);
	}
		
	// -- Engine Events -- // 
	
	override void EOnInit(IEntity owner)
	{
		// call our super. 
		super.EOnInit(owner);
		
		// add ourselves to the global function pointer. 
		// if one is already alive, ignored this attempt. 
		ParadoxTriggerFunctionLibrary.CreateTriggerManager(this); 		
	}	
	
	// -- Trigger Manager Methods -- // 
	
	// returns if the basic trigger map has any elements. 
	bool HasBasicTriggersInMap()
	{
		return !BasicTriggerMap.IsEmpty();
	}
	
	// returns if the faction trigger map has any elements. 
	bool HasFactionTriggersInMap()
	{
		return !FactionTriggerMap.IsEmpty();
	}
	
	// returns if we were able to find any triggers with a specific tag. If there are more 
	// triggers with that tag, we return the first element in the list. 
	bool FindBasicTriggerInstanceWithTag(string tagToFind, out SCR_ParadoxTriggerBase foundTrigger)
	{
		// if we do not have any triggers in the map, or the tag is empty. 
		if(!HasBasicTriggersInMap())
		{
			// null out the found trigger, and return false. 
			foundTrigger = null; 
			return false; 
		}
		else // else ... 
		{
			// return the first element from the array. 
			return ParadoxMapFunctionLibrary<string, SCR_ParadoxTriggerBase>.FindFirstArrayElementFromKey(BasicTriggerMap, tagToFind, foundTrigger);					
		}	
	}
	
	// returns if we were able to find any faction triggers with a specific tag. If there are more 
	// triggers with that tag, we return the first element in the list. 
	bool FindFactionTriggerInstanceWithTag(string tagToFind, out SCR_ParadoxFactionTrigger foundTrigger)
	{
		// if we do not have any triggers in the map, or the tag is empty. 
		if(!HasBasicTriggersInMap())
		{
			// null out the found trigger, and return false. 
			foundTrigger = null; 
			return false; 
		}
		else // else ... 
		{
			// return the first element from the array. 
			return ParadoxMapFunctionLibrary<string, SCR_ParadoxFactionTrigger>.FindFirstArrayElementFromKey(FactionTriggerMap, tagToFind, foundTrigger);					
		}
	}
	
	// returns if we could get a copy list from the master list. 
	bool FindBasicTriggerListWithTag(string tagToFind, out array<SCR_ParadoxTriggerBase> foundTriggers)
	{
		// if we do not have any triggers in the map, or the tag is empty. 
		if(!HasBasicTriggersInMap())
		{
			// if we have nothing, send a null array and return false. 
			foundTriggers = new array<SCR_ParadoxTriggerBase>(); 
			return false; 
		}
		else // else ... 
		{
			// attempt to find the trigger list that exists for a specific tag. 
			if(BasicTriggerMap.Find(tagToFind, foundTriggers))
			{
				return true; 
			}
			else // else ... 
			{
				// return a null array, and false. 
				foundTriggers = new array<SCR_ParadoxTriggerBase>(); 
				return false; 
			}			
		}
	}
	
	// returns if we could get a copy list from the master list. 
	bool FindFactionTriggerListWithTag(string tagToFind, out array<SCR_ParadoxFactionTrigger> foundTriggers)
	{
		// if we do not have any triggers in the map, or the tag is empty. 
		if(!HasFactionTriggersInMap())
		{
			// if we have nothing, send a null array and return false. 
			foundTriggers = new array<SCR_ParadoxFactionTrigger>(); 
			return false; 
		}
		else // else ... 
		{
			// attempt to find the trigger list that exists for a specific tag. 
			if(FactionTriggerMap.Find(tagToFind, foundTriggers))
			{
				return true; 
			}
			else // else ... 
			{
				// return a null array, and false. 
				foundTriggers = new array<SCR_ParadoxFactionTrigger>(); 
				return false; 
			}			
		}
	}
	
	// returns if we were able to add a trigger with a specific tag. 
	bool AddBasicTriggerWithTag(SCR_ParadoxTriggerBase triggerToAdd)
	{
		// if the trigger to add is null.. 
		if(!triggerToAdd)
		{
			// return false. 
			return false; 
		}
		else // else ... 
		{
			// add the element unqiuely to a list. 
			return ParadoxMapFunctionLibrary<string, SCR_ParadoxTriggerBase>.AddUnqiueObjectToArrayElmentList(BasicTriggerMap, triggerToAdd.GetTriggerTag(), triggerToAdd);
		}
	}
	
	// returns if we are able to add a faction trigger with its tag. 
	bool AddFactionTriggerWithTag(SCR_ParadoxFactionTrigger triggerToAdd)
	{
		// if the trigger to add is null.. 
		if(!triggerToAdd)
		{
			// return false. 
			return false; 
		}
		else // else ... 
		{
			// add the element unqiuely to a list. 
			return ParadoxMapFunctionLibrary<string, SCR_ParadoxFactionTrigger>.AddUnqiueObjectToArrayElmentList(FactionTriggerMap, triggerToAdd.GetTriggerTag(), triggerToAdd);
		}
	}
	
	bool RemoveBasicTriggerWithTag(SCR_ParadoxTriggerBase triggerToRemove)
	{
		// if the trigger to remove is null.. 
		if(!triggerToRemove)
		{
			// return false. 
			return false; 
		}
		else // else ... 
		{
			// remove the unique element from the maps internal list. 
			return ParadoxMapFunctionLibrary<string, SCR_ParadoxTriggerBase>.RemoveUnqiueObjectFromArrayElmentList(BasicTriggerMap, triggerToRemove.GetTriggerTag(), triggerToRemove);
		}	
	}
	
	bool RemoveFactionTriggerWithTag(SCR_ParadoxFactionTrigger triggerToRemove)
	{
		// if the trigger to remove is null.. 
		if(!triggerToRemove)
		{
			// return false. 
			return false; 
		}
		else // else ... 
		{
			// remove the unique element from the maps internal list. 
			return ParadoxMapFunctionLibrary<string, SCR_ParadoxFactionTrigger>.RemoveUnqiueObjectFromArrayElmentList(FactionTriggerMap, triggerToRemove.GetTriggerTag(), triggerToRemove);
		}	
	}	
};