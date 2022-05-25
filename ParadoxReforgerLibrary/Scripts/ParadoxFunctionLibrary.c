// List of helper functions designed to reduce the need for copy paste code. 
// -- Parad0x
//
// to use any of this, add this script to your project. 
// then call ParadoxFunctionLibrary.<methodneeded>


//------------------------------------------------------------------
// Generic Helper Library 											-
// Generic methods that do not fit nicely into one category. 		-
//------------------------------------------------------------------
class ParadoxFunctionLibrary
{	
	// -- Constructor and Destructor -- // 
	void ParadoxFunctionLibrary()
	{
	}
	
	void ~ParadoxFunctionLibrary()
	{
	}
	
	// -- Rank Methods -- // 
	// returns if the character rank valid
	static bool IsCharacterRankValid(IEntity characterToCheck)
	{
		return SCR_CharacterRankComponent.GetCharacterRank(characterToCheck) != ECharacterRank.INVALID;
	}	
	
	// returns if character a and characters b rank is the same. 
	static bool AreCharactersSameRank(IEntity characterA, IEntity characterB)
	{
		return SCR_CharacterRankComponent.GetCharacterRank(characterA) == SCR_CharacterRankComponent.GetCharacterRank(characterB);		
	}
	
	// return if the character A rank is higher than character rank B. 
	static bool IsCharacterARankHigher(IEntity characterA, IEntity characterB)
	{
		return SCR_CharacterRankComponent.GetCharacterRank(characterA) > SCR_CharacterRankComponent.GetCharacterRank(characterB);	
	}
		
	// returns if the characters rank below a specific value 
	static bool IsCharacterBelowRankThreshold(IEntity characterToCheck, ECharacterRank rankThreshold)
	{
		return SCR_CharacterRankComponent.GetCharacterRank(characterToCheck) < rankThreshold;
	}
	
	// returns if the characters rank is at a specific value
	static bool IsCharacterRankAtThreshold(IEntity characterToCheck, ECharacterRank rankThreshold)
	{
		return SCR_CharacterRankComponent.GetCharacterRank(characterToCheck) == rankThreshold;
	}
	
	// return if the character's rank is above a specific value 
	static bool IsCharacterRankAboveThreshold(IEntity characterToCheck, ECharacterRank rankThreshold)
	{
		return SCR_CharacterRankComponent.GetCharacterRank(characterToCheck) > rankThreshold;
	}	
	
	// -- Faction Methods -- // 
	// returns if we can get the character faction off an entity. 
	// if the result is true, then outFaction will be set. 
	static bool IsAbleToGetCharacterFaction(IEntity characterToProcess, out Faction outFaction)
	{
		// if we get a null character. 
		if(!characterToProcess)
		{
			// return a null faction object, then bail. 
			outFaction = null; 
			return false; 
		}
		else // else ... 
		{
			// cast the character to a character. 
			SCR_ChimeraCharacter castedCharacter = SCR_ChimeraCharacter.Cast(characterToProcess);
			
			// if our cast failed. 
			if(!castedCharacter)
			{
				// return a null faction object, then bail. 
				outFaction = null; 
				return false; 
			}
			else // else... 
			{
				// get the faction
				outFaction = castedCharacter.GetFaction(); 
				
				// return if that faction is null or not
				return outFaction != null; 				
			}
		}
	}	
	
	// returns if character A is friendly towards character B. 
	// expensive due to a cast, try to use this only when needed for max performance. 
	static bool IsCharacterFriendly(IEntity characterA, IEntity characterB)
	{
		// create temp variables to be filled out by the below calls. 
		Faction characterAFaction; 
		Faction characterBFaction; 
		
		// if we are able to get valid character factions for character A and character B
		if(IsAbleToGetCharacterFaction(characterA, characterAFaction) && IsAbleToGetCharacterFaction(characterB, characterBFaction))
		{
			// return if those characters are friendly or not. 
			return characterAFaction.IsFactionFriendly(characterBFaction); 
		}
		else // else ... 
		{
			// if anything goes wrong, bail out. 
			return false; 
		}		
	}
	
	// -- Array Methods -- // 
	// returns an array that order that has been randomized. 
	static bool RandomizeArrayOrder(ref array<T> inOutArrayToRandomize)
	{
		// if we have no array....
		if(inOutArrayToRandomize.IsEmpty())
		{
			// bail out. 
			return false; 
		}
		else // else ... 
		{
			// for each index in our array... 
			for(int i = 0; i < inOutArrayToRandomize.Count(); i++)
			{
				// have the array swap from the current position to a random position in the array.  
				inOutArrayToRandomize.SwapItems(i, inOutArrayToRandomize.GetRandomIndex()); 		
			}	
			
			// return we did a randomization. 
			return true; 
		}		
	}
};



