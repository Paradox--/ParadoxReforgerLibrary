// A basic asset manager. Allows for scripts of designers and engineers to quickly access resources and spawn them 
// without needing to bake them into a bunch of scripts and components.  This class can be accessed at any time from 
// the asset manager function library. 

//------------------------------------------------------------------
// Resource Container	 											-
// A basic struct as a class that allows you to pair a string 		-
// tag with a resource name.  This allows for a bit more 			-
// flexablity when it comes to finding resource. 					-
//------------------------------------------------------------------
[BaseContainerProps()]
class ParadoxResouceContainer 
{
	// -- Properties -- // 
	
	// the resource tag
	[Attribute("NULL", UIWidgets.EditBox, desc: "A string tag for this resource container")]
	string ResourceTag;
	
	[Attribute("NULL_RESOURCE", UIWidgets.ResourceNamePicker, desc: "The Prefab that we should spawn or load. A string name of a resource to be referenced by a tag.")]
	ResourceName NameOfResource; 
		
	// -- Methods  -- // 
	bool IsValid()
	{
		return !ResourceTag.IsEmpty() && !NameOfResource.IsEmpty();
	}
	
	bool IsResourceNameForTag(string OtherTag)
	{
		return ResourceTag == OtherTag; 
	}
	
	string GetResourceTag()
	{
		return ResourceTag; 
	}
	
	ResourceName GetResourceName()
	{
		return NameOfResource; 
	}
};

//------------------------------------------------------------------
// Asset Manager Class	 											-
// The class for the asset manager.									-
//------------------------------------------------------------------
[EntityEditorProps(category: "ParadoxReforgerLibrary/Entities/Managers", description: "A basic asset manager class. Holds references to assets that might need to be accessed at random.")]
class ParadoxAssetManagerBaseClass: GenericEntityClass
{
};

//------------------------------------------------------------------
// Asset Manager		 											-
// An asset manager class that allow outside classes to store 		-
// data and grab it when they need it.  							- 
//------------------------------------------------------------------
class ParadoxAssetManagerBase: GenericEntity
{
	// -- Class Properties -- // 
	
	[Attribute("", UIWidgets.Object, desc: "A list of assets that are under this managers control to find and be used by outside classes.", category: "Manager Settings")]
	ref array<ref ParadoxResouceContainer> assetsToManage; 
	
	// --  Destructor -- // 
	void ~ParadoxAssetManagerBase()
	{
		// nuke our resources
		assetsToManage.Clear(); 
		
		// nuke the asset manager. 
		ParadoxAssetFunctionLibrary.DestroyAssetManager(this); 	
	}
	
	// -- Engine Events -- // 
	
	override void EOnInit(IEntity owner)
	{
		// call our super. 
		super.EOnInit(owner);
		
		// add ourselves to the global function pointer. 
		// if one is already alive, ignored this attempt. 
		ParadoxAssetFunctionLibrary.CreateAssetManager(this); 		
	}
	
	// -- Methods -- // 
	
	// returns if we have any assets to manage. 
	bool HasAnyAssetsToManage() 
	{
		return assetsToManage.Count() > 0; 
	}
	
	// returns if we have container known by a specific tag. 
	private bool FindParadoxResourceContainerForTag(string AssetTag, out ParadoxResouceContainer Container)
	{
		// if we get a null tag, or if we have nothing to manage. 
		if(AssetTag.IsEmpty() || !HasAnyAssetsToManage())
		{
			// null out the container and retunr. 
			Container = null; 
			return false; 
		}
		else // else ... 
		{
			// for the assets under our control. 
			for(int i = 0; i < assetsToManage.Count(); i++)
			{
				// get a pointer to the current container. 
				ref ParadoxResouceContainer CurrentContainer = assetsToManage.Get(i);
				
				// if the pointer is valid, and the resource has the same tag as the requested tag. 
				if(CurrentContainer.IsValid() && CurrentContainer.IsResourceNameForTag(AssetTag))
				{
					// save the pointer. 
					Container = CurrentContainer; 
					
					// return if we found it. 
					return true;
				}
			}
			
			// null out the container and return false if we didnt find it. 
			Container = null; 
			return false; 
		}
	}
	
	// returns if we were able to load and spawn an asset internally for inline calls. 
	private bool RequestInlineLoadAndSpawnOfAssetInternal(string AssetTag, out IEntity SpawnedPrefab, vector InternalVector = vector.Zero, IEntity InternalEntity = null)
	{
		// if we get a null tag. 
		if(AssetTag.IsEmpty())
		{
			// null out the prefab and retunr. 
			SpawnedPrefab = null; 
			return false; 
		}
		else // else ... 
		{
			// create a container that we will fill out from our found method. 
			ParadoxResouceContainer FoundContainer = null; 
			
			// try to find it. 
			if(FindParadoxResourceContainerForTag(AssetTag, FoundContainer))
			{
				// load or pull it from the cache. 
				Resource LoadedResource = Resource.Load(FoundContainer.GetResourceName());
				
				// if we do not have an entity to use. 
				if(!InternalEntity)
				{
					// spawn the prefab
					SpawnedPrefab = GetGame().SpawnEntityPrefab(LoadedResource, null, ParadoxFunctionLibrary.CreateSpawnParams(ETransformMode.WORLD, InternalVector));
				}
				else // else ... 
				{
					// spawn the prefab
					SpawnedPrefab = GetGame().SpawnEntityPrefab(LoadedResource, null, ParadoxFunctionLibrary.CreateSpawnParamsAtEntity(InternalEntity, ETransformMode.WORLD));
				}			
				
				// return if that prefab is valid 
				return SpawnedPrefab != null; 
			}
			else
			{
				// null out the prefab and return false if we couldn't find it. 
				SpawnedPrefab = null; 
				return false; 
			}
		}
	
	}
	
	// returns if we were able to inline load and spawn a prefab at a location. 
	// the spawned object is returned as a param.  
	bool RequestInlineLoadAndSpawnOfAssetAtLocation(string AssetTag, vector SpawnLocation, out IEntity SpawnedPrefab)
	{
		return RequestInlineLoadAndSpawnOfAssetInternal(AssetTag, SpawnedPrefab, SpawnLocation); 
	}
	
	// returns if we were able to inline load and spawn a prefab at an entity. 
	// the spawned object is returned as a param.  
	bool RequestInlineLoadAndSpawnOfAssetAtEntity(string AssetTag, IEntity EntityToSpawnAt, out IEntity SpawnedPrefab)
	{
		return RequestInlineLoadAndSpawnOfAssetInternal(AssetTag, SpawnedPrefab, vector.Zero, EntityToSpawnAt); 
	}
	
	// returns if we were able to find a resource name from the inputed tag. 
	bool RequestResourceNameFromTag(string AssetTag, out ResourceName FoundResourceName)
	{	
		// if we get a null tag. 
		if(AssetTag.IsEmpty())
		{
			// null out the resource name and return false. 
			FoundResourceName = ""; 
			return false; 
		}
		else // else ... 
		{
			// create a container that we will fill out from our found method. 
			ParadoxResouceContainer FoundContainer = null; 
			
			// try to find it. 
			if(FindParadoxResourceContainerForTag(AssetTag, FoundContainer))
			{
				FoundResourceName = FoundContainer.GetResourceName(); 
				return !FoundResourceName.IsEmpty(); 
			}
			else // else ... 
			{
				// null out the resource name and return false. 
				FoundResourceName = ""; 
				return false; 
			}
		}
	}
	
	// returns the number of assets under our control. 
	int GetAssetsToManageCount()
	{
		return assetsToManage.Count();
	}
	
};





