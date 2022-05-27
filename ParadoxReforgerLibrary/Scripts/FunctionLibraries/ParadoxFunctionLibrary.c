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
	//-----------------------//
	// -- Generic Methods -- // 
	//-----------------------//
	
	// THIS IS NOT POSSIBLE AT THIS TIME. Saving for the day it is.  
	// returns if we are able to find a valid world from the world context. 
	// mostly used to make sure the world point is non null. 
	/*static bool GetWorldChecked(IEntity worldContext, out BaseWorld outFoundWorld)
	{
		// if we have bad input....
		if(!worldContext)
		{
			// reutrn a null value.
			outFoundWorld = null;
			return false;
		}
		else // else ... 
		{
			// get the world from the context
			outFoundWorld = worldContext.GetWorld();
			
			// return if that world is null or not. 
			return outFoundWorld != null; 
		}
	}*/
	
	//-----------------------//
	// -- Rank Methods 	  -- // 
	//-----------------------//
	
	
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
	
	//-----------------------//
	// -- Faction Methods -- //
	//-----------------------//
	
	 
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
	// think of this as asking if the characters are on the same team. 
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
	
	// returns if character A is hostile towards character B
	// think of this as asking if the character are on opposite teams. 
	static bool IsCharacterHostile(IEntity characterA, IEntity characterB)
	{
		// create temp variables to be filled out by the below calls. 
		Faction characterAFaction; 
		Faction characterBFaction; 
		
		// if we are able to get valid character factions for character A and character B
		if(IsAbleToGetCharacterFaction(characterA, characterAFaction) && IsAbleToGetCharacterFaction(characterB, characterBFaction))
		{
			// return if those characters are friendly or not. 
			return characterAFaction.IsFactionEnemy(characterBFaction); 
		}
		else // else ... 
		{
			// if anything goes wrong, bail out. 
			return false; 
		}	
	}
	
	//-----------------------//
	// -- Time Methods 	  -- // 
	//-----------------------//
	
	
	// returns if enough time has passed between the starting time and the time to wait. 
	// computes in miliseconds. 
	static bool HasTimeElasped(IEntity worldContext, float startingTime, float timeToWaitInMS)
	{
		return GetTimeElapsed(worldContext, startingTime) >= timeToWaitInMS; 
	}
	
	// returns if enough time has passed between the starting time and the time to wait. 
	// computes in seconds. 
	static bool HasTimeElaspedInSeconds(IEntity worldContext, float startingTime, float timeToWaitInSeconds)
	{
		return GetTimeElapsedInSeconds(worldContext, startingTime) >= timeToWaitInSeconds; 
	}
	
	// returns an inputed time that is in miliseconds to seconds.  
	static float ConvertTimeFromMSToSeconds(float timeInMS)
	{
		return timeInMS / 1000.0; 
	}
	
	// returns an inputed time in seconds as time in MS
	static float ConvertTimeFromSecondsToMS(float timeInSeconds)
	{
		return timeInSeconds * 1000.0; 
	}
	
	// returns the time elapsed between now and the starting time in miliseconds. 
	// if the world context is null or the starting time is less than or equal to zero this will fail. 
	static float GetTimeElapsed(IEntity worldContext, float startingTime)
	{
		// if we have no world context or the starting time is invalid. 
		if(!worldContext || startingTime <= 0.0)
		{
			return 0.0; 
		}
		else // else ... 
		{
			// create a pointer for the found world. 
			BaseWorld foundWorld = worldContext.GetWorld();
			
			// if the world is null for some reason...
			if(!foundWorld)
			{
				return 0.0; 
			}
			else // else ... 
			{
				// return the delta time between the starting time and the current worlds time.				
				return Math.AbsFloat((startingTime - foundWorld.GetWorldTime()));
			}
		}	
	}
	
	// returns the amount of time in seconds between the starting time and now.
	static float GetTimeElapsedInSeconds(IEntity worldContext, float startingTime)
	{
		// return the result of the current time elapsed in MS adjusted to seconds. 
		return ConvertTimeFromMSToSeconds(GetTimeElapsed(worldContext, startingTime)); 
	}
	
	// returns the current world time in seconds. 
	static float GetTimeInSeconds(IEntity worldContext)
	{
		// if we have no world context. 
		if(!worldContext)
		{
			return 0.0; 
		}
		else // else ... 
		{
			// create a pointer for the found world. 
			BaseWorld foundWorld = worldContext.GetWorld();
			
			// if the world is null for some reason...
			if(!foundWorld)
			{
				return 0.0; 
			}
			else
			{
				// return the time in seconds. 
				return ConvertTimeFromMSToSeconds(foundWorld.GetWorldTime()); 
			}
		}	
	}
};





