// List of helper functions designed to reduce the need for copy paste code. 
// -- Parad0x
//
// to use any of this, add this script to your project. 
// then call ParadoxFunctionLibrary.<methodneeded>


//------------------------------------------------------------------
// Asset Helper Library 											-
// All methods here for asset and the asset manager. 				-
//------------------------------------------------------------------
class ParadoxAssetFunctionLibrary
{	
	// -- Runtime Properties -- // 
	
	// a runtime pointer for the runtime manager, this is created and 
	// and destroyed as needed.  
	static ParadoxAssetManagerBase runtimeManagerPtr = null; 
	
	// -- Manager Methods -- // 
	
	// returns if there is a valid function library manager pointer.
	static bool HasAssetManager()
	{
		return runtimeManagerPtr != null; 
	}
	
	// returns if we were able to inline load and spawn a prefab at a location. 
	// the spawned object is returned as a param.  
	static bool RequestInlineLoadAndSpawnOfAssetAtLocation(string AssetTag, vector SpawnLocation, out IEntity SpawnedPrefab)
	{
		// if we have no asset manager. 
		if(!HasAssetManager())
		{
			// null out the returned prefab, and return false. 
			SpawnedPrefab = null; 
			return false; 
		}
		else // else ... 
		{
			// request the inline load. 
			return GetAssetManager().RequestInlineLoadAndSpawnOfAssetAtLocation(AssetTag, SpawnLocation, SpawnedPrefab);
		}
	}
	
	// returns if we were able to inline load and spawn a prefab at an entity. 
	// the spawned object is returned as a param.  
	static bool RequestInlineLoadAndSpawnOfAssetAtEntity(string AssetTag, IEntity EntityToSpawnAt, out IEntity SpawnedPrefab)
	{
		// if we have no asset manager. 
		if(!HasAssetManager())
		{
			// null out the returned prefab, and return false. 
			SpawnedPrefab = null; 
			return false; 
		}
		else // else ... 
		{
			// request the inline load. 
			return GetAssetManager().RequestInlineLoadAndSpawnOfAssetAtEntity(AssetTag, EntityToSpawnAt, SpawnedPrefab);
		}
	}
	
	// returns if we were able to find a resource name from the inputed tag. 
	static bool RequestResourceNameFromTag(string AssetTag, out ResourceName FoundResourceName)
	{	
		// if we have no asset manager. 
		if(!HasAssetManager())
		{
			// null out the resource name and return false. 
			FoundResourceName = ""; 
			return false;  
		}
		else // else ... 
		{
			// request the resource name. 
			return GetAssetManager().RequestResourceNameFromTag(AssetTag, FoundResourceName);
		}
	}
	
	
	// returns the current runtime asset manager pointer. 
	static ParadoxAssetManagerBase GetAssetManager()
	{
		return runtimeManagerPtr; 
	}
	
	// seed the asset manager pointer. This is set by an instance of the Paradox asset manager. 
	static void CreateAssetManager(ParadoxAssetManagerBase newManager)
	{
		// if we already have a manager... 
		if(HasAssetManager())
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
	
	// cleans up the current asset manager pointer. 
	static void DestroyAssetManager(ParadoxAssetManagerBase managerToRemove)
	{
		// if we do not have a runtime pointer, or this isnt our runtime global pointer.  
		if(!HasAssetManager() || (GetAssetManager() != managerToRemove))
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