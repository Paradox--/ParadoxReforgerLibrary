// Base class for paradox triggers. These are meant to be inherited from to add your own functionality to them. 
//
// This trigger allows for basic overlaps 
//
// -> A basic overlap is one that is always going to happen if this triggered is enabled. 
//
// If you want to listen to the trigger going off use: 
// GetOnActivate() for start overlap 
// GetOnDeactivate() for End overlap events. 
//
// Workbench Editor Note: The entity editor props category will be created with this trigger.  So in your world you can simple drag this trigger in like any regular trigger. 
// -- Paradox

[EntityEditorProps(category: "ParadoxReforgerLibrary/Entities/Triggers", description: "A basic trigger class with ability to broadcast when it can and can't be triggered.")]
class SCR_ParadoxTriggerBaseClass: SCR_BaseTriggerEntityClass
{
};

class SCR_ParadoxTriggerBase : SCR_BaseTriggerEntity
{
	// -- Class Properties -- // 
	
	// can this trigger be activated? or do we need a script or event to enable us? 
	[Attribute(defvalue: "false", uiwidget: UIWidgets.CheckBox, desc: "If true, this trigger will accept overlap events", category: "Trigger Settings")]
	bool m_bCanBeTriggered; 
	
	[Attribute("NULL", UIWidgets.EditBox, desc: "A string tag for this trigger, useful for get trigger of tag functions.", category: "Trigger Settings")]
	string m_TriggerTag; 
	
	// the amount of objects overlapping us. 
	protected int m_OverlappedCount = 0; 	
	
	// Delegate for when our triggers can be triggered state changes. Allows objects to be notified when the state changes. 
	// returns the state and pointer to the trigger that fired it. Example Catch of this void MyMethod(bool bNewState, SCR_ParadoxTriggerBase triggerThatUpdatedState)
	ref ScriptInvoker m_OnTriggerCanBeTriggerStateChanged = new ScriptInvoker();
	
	// -- Trigger Methods -- // 
	// returns if we can be triggered or not. 
	bool CanBeTriggered() 
	{
		return m_bCanBeTriggered; 
	}
	
	// returns if we can add this character to the trigger. 
	// overload this your triggers for ease of use. 
	bool IsCharacterValidForOverlap(SCR_ChimeraCharacter characterToCheck)
	{
		// overload me for you own needs. 
		return characterToCheck != null; 
	}	
	
	// filter overlap method, returns if we can add this object to the count or not 
	override bool ScriptedEntityFilterForQuery(IEntity ent) 
	{
		// if the object is invalid 
		if(!ent || !CanBeTriggered())
		{
			// we cant add this. 
			return false; 
		}
		else // else ... 
		{
			// if the object is not alive... 
			if(!IsAlive(ent))
			{
				return false; 
			}
			else // else ... 
			{
				// cast the object to a character. 
				SCR_ChimeraCharacter castedCharacter = SCR_ChimeraCharacter.Cast(ent);		
				
				// return if this character is valid for overlaps. 
				return IsCharacterValidForOverlap(castedCharacter);		
			}			
		}
    }
	
	// checks if a trigger has a null tag, i.e. an empty tag. 
	bool DoesTriggerHaveNullTag() 
	{
		return GetTriggerTag().IsEmpty() || (GetTriggerTag() == "NULL"); 
	}
	
	// checks if the this trigger has a specific tag. 
	bool DoesTriggerHaveTag(string otherTag)
	{
		return GetTriggerTag() == otherTag; 
	}
	
	// returns the overlapping object count. 
	int GetOverlappingObjectCount() 
	{
		return m_OverlappedCount; 
	}
	
	string GetTriggerTag()
	{
		return m_TriggerTag;
	}
	
	// returns the state update delegate
	ScriptInvoker GetOnTriggerCanUpdateStateChange()
	{
		return m_OnTriggerCanBeTriggerStateChanged;
	}		
	 
	// overridden on valid overlap start event. 
    override void OnActivate(IEntity ent)
    {
		// call our overlap super. 
		super.OnActivate(ent);
		
		// increase the count. 
        ++m_OverlappedCount; 	
    }

 
	// overriden on valid overlap end eveent. 
    override void OnDeactivate(IEntity ent)
    {    
		// call our overlap super. 
		super.OnDeactivate(ent);
		
		// decrease the count. 
       	--m_OverlappedCount; 
    }
	
	// sets if this trigger can be triggered or not. 
	void SetCanBeTriggered(bool bNewState)
	{
		// if the new state is going to be different than our state. 
		if(bNewState != m_bCanBeTriggered)
		{
			// call our delegate. 
			m_OnTriggerCanBeTriggerStateChanged.Invoke(bNewState, this); 
		}		
		
		// set our new state. 
		m_bCanBeTriggered = bNewState; 
	}	
};



 
    