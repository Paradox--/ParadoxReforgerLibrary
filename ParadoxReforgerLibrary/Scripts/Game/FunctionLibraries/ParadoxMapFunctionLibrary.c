// A basic function library for common Map container methods. Cut down on copy paste code. 
// -- Paradox 


class ParadoxMapFunctionLibrary<Class TKey, Class TValue>
{
	//------------------------//
	// -- Map Methods   	--// 
	//-----------------------//
	
	// takes an key and value pair for a map where the first element is a single object, and the second element is an array. 
	// returns if we found a valid object. 
	static bool FindFirstArrayElementFromKey(inout map<TKey, ref array<TValue>> inOutMap, TKey KeyToFind, out TValue FirstElement)
	{
		// if the incoming map is null, or the key is null. 
		if(inOutMap.IsEmpty() || !KeyToFind)
		{
			FirstElement = null; 
			return false; 
		}
		else // else ... 
		{
			array<TValue> tempArray; 			
			
			// search the map for the correct array. 
			if(inOutMap.Find(KeyToFind, tempArray))
			{
				// if the array is empty. 
				if(tempArray.IsEmpty())
				{
					// null out the found element, and return false. 
					FirstElement = null; 
					return false;
				}
				else // else ... 
				{
					// otherwise snag our first instance 
					FirstElement = tempArray.Get(0);
					
					// return if that pointer is valid. Reduce the extra check on the caller. 
					return FirstElement != null; 				
				}
			}
			else // else ... 
			{
				// null out the found element, and return false. 
				FirstElement = null; 
				return false;
			}	
		}	
	}
	
	// add a element unique to 
	static bool AddUnqiueObjectToArrayElmentList(inout map<TKey, ref array<TValue>> inOutMap, TKey KeyToFind, TValue ElementToAdd)
	{
		// if we get bad data... 
		if(!KeyToFind || ElementToAdd)
		{
			return false; 
		}
		else // else ... 
		{
			// if we have no existing data at all... 
			if(inOutMap.IsEmpty() || !inOutMap.Contains(KeyToFind))
			{
				// create a container. 
				array<TValue> newArray = new ref array<TValue>(); 
			
				// add our first element. 
				newArray.Insert(ElementToAdd);			
			
				// insert it, and return if its a valid index. 
				return inOutMap.Insert(KeyToFind, newArray) >= 0; 
			}
			else // else ... 
			{
				// build a temp container, we will snag this from the map. 
				ref array<TValue> currentArray = new ref array<TValue>(); 
				
				// attempt to find the trigger list that exists for a specific tag. 
				if(inOutMap.Find(KeyToFind, currentArray))
				{
					// for each of our elements.
					for(int i = 0; i < currentArray.Count(); i++)
					{
						// if we find the same object. 
						if(currentArray.Get(i) == ElementToAdd)
						{
							// return that it wasnt added.  
							return false; 
						}
					}	
					
					// insert the element at the end. 
					return currentArray.Insert(ElementToAdd) >= 0;
				}
				else // else ... 
				{
					return false; 
				} 			
			}		
		}	
	}
	
	// remove a unique element 
	static bool RemoveUnqiueObjectFromArrayElmentList(inout map<TKey, ref array<TValue>> inOutMap, TKey KeyToFind, TValue ElementToRemove)
	{
		// if we get bad data... 
		if(!KeyToFind || ElementToRemove)
		{
			return false; 
		}
		else // else ... 
		{
			// if we have no existing data at all... 
			if(inOutMap.IsEmpty() || !inOutMap.Contains(KeyToFind))
			{
				// if we failed to find anything with that key. 
				return false; 
			}
			else // else ... 
			{
				// build a temp container, we will snag this from the map. 
				ref array<TValue> currentArray = new ref array<TValue>(); 
				
				// attempt to find the trigger list that exists for a specific tag. 
				if(inOutMap.Find(KeyToFind, currentArray))
				{
					// for each of our elements.
					for(int i = currentArray.Count() - 1; i >= 0 ; i--)
					{
						// if we find the same object. 
						if(currentArray.Get(i) == ElementToRemove)
						{
							// remove the object, and return true. 
							currentArray.Remove(i);
							return true; 
						}
					}	
					
					// return false if we didnt find anything. 
					return false;
				}
				else // else ... 
				{
					return false; 
				} 			
			}		
		}	
	}
	
	
	
};



