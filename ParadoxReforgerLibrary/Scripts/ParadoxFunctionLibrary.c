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
	// -- Array Methods   -- // 
	//-----------------------//
	
	// returns an array that order that has been randomized. 
	static bool RandomizeArrayOrder(inout array<T> inOutArrayToRandomize)
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
		return GetTimeElapsedInSeconds(worldContext, startingTime) >= timeToWaitInMS; 
	}
	
	// returns an inputed time that is in miliseconds to seconds.  
	static float ConvertTimeFromMSToSeconds(float timeInMS)
	{
		return timeInMS / 1000.0; 
	}
	
	// returns an inputed time in seconds as time in MS
	static float ConvertTimeFromSecondsToMS(float timeInSeconds)
	{
		return timeInMS * 1000.0; 
	}
	
	// returns the time elapsed between now and the starting time in miliseconds. 
	// if the world context is null or the starting time is less than or equal to zero this will fail. 
	static float GetTimeElapsed(IEntity worldContext, float startingTime)
	{
		// if we have bad input....
		if(!worldContext || startingTime <= 0.f)
		{
			// reutrn a null value.
			return 0.0;
		}
		else // else ... 
		{
			// get the world from the context
			BaseWorld world = worldContext.GetWorld();
			
			// make sure that world pointer is valid before accessing
			if(!world)
			{
				// if not return null. 
				return 0.0; 
			}
			else // else ... 
			{
				// return the delta time between the starting time and the current worlds time.				
				return Math.AbsFloat(startingTime - world.GetWorldTime());
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
		// if we have bad input....
		if(!worldContext)
		{
			// reutrn a null value.
			return 0.0;
		}
		else // else ... 
		{
			// get the world from the context
			BaseWorld world = worldContext.GetWorld();
			
			// make sure that world pointer is valid before accessing
			if(!world)
			{
				// if not return null. 
				return 0.0; 
			}
			else // else ... 
			{
				// return the time in seconds. 
				return ConvertTimeFromMSToSeconds(world.GetWorldTime()); 
			}
		}
	}
};



