// Template Array function library class to allow for arrays of all types to use this in a templated manner. 
// This function library holds common array methods that might be useful for your project. 
// -- Paradox 
//
// Example:
// array<IEntity> MyArray = array<IEntity>(); // array declared at some point 
//
// when we need to use it:
// if(ParadoxArrayFunctionLibrary<IEntity>.IsValidIndexForArray(MyArray, SomeIndex))
// {
// 		// some code that runs.... 
// }


class ParadoxArrayFunctionLibrary<Class T>
{
	//-----------------------//
	// -- Array Methods   -- // 
	//-----------------------//
	
	// checks if the index provided is a valid index in the scope of the provided array. 
	static bool IsValidIndexForArray(ref array<T> inOutArray, int indexToCheck)
	{
		return inOutArray.Count() >= 1 && (indexToCheck >= 0 && indexToCheck < inOutArray.Count());
	}
	
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
	
	
	// attempts to add an object to an array of the same type. checks the whole array to make sure that object does 
	// not already exist. THIS IS O(n) as it will search the whole array with each add. 
	static int InsertUnqiue(ref array<T> inOutArray, T uniqueObject)
	{
		// for each index in our array... 
		for(int i = 0; i < inOutArray.Count(); i++)
		{
			// if we find the same object. 
			if(inOutArray.Get(i) == uniqueObject)
			{
				// return an invalid index. 
				return -1; 
			}
		}	
		
		// if we found nothing add this to the end, and return its index. 
		return inOutArray.Insert(uniqueObject);
	}
};