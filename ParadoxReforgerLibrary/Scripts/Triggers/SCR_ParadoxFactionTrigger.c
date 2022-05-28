// This is a child of the paradox basic trigger. This trigger will only go off if a valid faction character enters its area
// of concern.  
// -- Paradox

[EntityEditorProps(category: "ParadoxReforgerLibrary/Entities/Triggers", description: "A basic trigger class that only allow overlap events for specific factions.")]
class SCR_ParadoxFactionTriggerClass: SCR_ParadoxTriggerBaseClass
{
};

class SCR_ParadoxFactionTrigger : SCR_ParadoxTriggerBase
{
	// -- Class Properties -- // 
	
	// can we trigger on the US Faction
	[Attribute(defvalue: "false", uiwidget: UIWidgets.CheckBox, desc: "If true, this trigger will accept overlap events for the US Faction", category: "Faction Trigger Settings")]
	bool m_bCanTriggerOnUSFaction; 
	
	// can we trigger on the USSR Faction
	[Attribute(defvalue: "false", uiwidget: UIWidgets.CheckBox, desc: "If true, this trigger will accept overlap events for the USSR Faction", category: "Faction Trigger Settings")]
	bool m_bCanTriggerOnUSSRFaction; 
	
	// can we trigger on the FIA Faction
	[Attribute(defvalue: "false", uiwidget: UIWidgets.CheckBox, desc: "If true, this trigger will accept overlap events for the FIA Faction", category: "Faction Trigger Settings")]
	bool m_bCanTriggerOnFIAFaction;
	
	// can we trigger on a custom specified faction
	[Attribute(defvalue: "false", uiwidget: UIWidgets.CheckBox, desc: "If true, this trigger will accept overlap events for the Custom Faction", category: "Faction Trigger Settings")]
	bool m_bCanTriggerOnCustomFaction; 
	
	[Attribute("MyCustomFaction", UIWidgets.EditBox, desc: "The custom string representation of a custom faction", category: "Faction Trigger Settings")]
	string m_CustomFactionIDString; 
	
	// -- Constructor / Destructor -- // 
	
	void ~SCR_ParadoxFactionTrigger()
	{
		// if we can auto register, and we are on the server... 
		if(CanTriggerAutoRegister() && Replication.IsServer())
		{
			// remove ourselves on destruction. 
			// this allows desginers, or other scripts to destroy these at will. 
			ParadoxTriggerFunctionLibrary.RemoveFactionTriggerWithTag(this);
		}
	}
	
	// -- Faction Trigger Methods -- // 
	
	// returns if we can accept any overlaps from the US Faction characters
	bool IsAbleToOverlapUSFactionCharacters()
	{
		return m_bCanTriggerOnUSFaction;
	}
	
	// returns if we can accept any overlaps from the USSR Faction characters
	bool IsAbleToOverlapUSSRFactionCharacters()
	{
		return m_bCanTriggerOnUSSRFaction;
	}
	
	// returns if we can accept any overlaps from the FIA Faction characters
	bool IsAbleToOverlapFIAFactionCharacters()
	{
		return m_bCanTriggerOnFIAFaction;
	}
	
	// returns if we can accept any overlaps from the custom Faction characters
	bool IsAbleToOverlapCustomFactionCharacters()
	{
		return m_bCanTriggerOnCustomFaction;
	}	
	
	// returns if we can accept any faction overlaps at all.
	bool IsAbleToAcceptAnyFactionOverlaps()
	{
		return IsAbleToOverlapUSFactionCharacters() || IsAbleToOverlapUSSRFactionCharacters() || IsAbleToOverlapFIAFactionCharacters() || IsAbleToOverlapCustomFactionCharacters();
	}	
	
	// returns if we can add this character to the trigger. 
	override bool IsCharacterValidForOverlap(SCR_ChimeraCharacter characterToCheck)
	{
		// if we get an invalid character, or we are not accepting any overlaps at this time. 
		if(!characterToCheck || !IsAbleToAcceptAnyFactionOverlaps())
		{
			// return false. 
			return false; 
		}
		else // else .... 
		{
			// we already check for the character being alive, just need to check for everything else we need. 
			
			// snag their Faction
			Faction CharactersFaction = characterToCheck.GetFaction(); 
		
			// do we need to check for a US Character, and this is a US character. 
			if(IsAbleToOverlapUSFactionCharacters() && ParadoxFunctionLibrary.IsUSFaction(CharactersFaction))
			{
				// if we passed. 
				return true; 
			}
			// else if we can check for USSR and this is a USSR charcter. 
			else if(IsAbleToOverlapUSSRFactionCharacters() && ParadoxFunctionLibrary.IsUSSRFaction(CharactersFaction))
			{
				// if we passed. 
				return true; 
			}
			// else if we can check for FIA and this is an FIA
			else if(IsAbleToOverlapFIAFactionCharacters() && ParadoxFunctionLibrary.IsFIAFaction(CharactersFaction))
			{
				// if we passed. 
				return true; 
			}
			// else if we can check for custom classes and this is the custom class we are looking for. 
			else if(IsAbleToOverlapCustomFactionCharacters() && ParadoxFunctionLibrary.IsFactionTheSame(CharactersFaction, GetCustomFactionIDString()))
			{
				// if we passed. 
				return true; 
			}
			else // else ... 
			{
				// in all other cases if we were not able to be found, return false . 
				return false; 
			}		
		}
	}
	
	// returns the custom faction string. 
	string GetCustomFactionIDString()
	{
		return m_CustomFactionIDString; 
	}	
	
	// add a trigger to the manager, but we make sure we add the correct type. 
	override void OnTriggerWaitToInit()
	{
		// add this element to the list. 
		ParadoxTriggerFunctionLibrary.AddFactionTriggerWithTag(this);	
	}
	
};