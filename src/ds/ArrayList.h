#pragma once

template <class ItemType>
class ArrayList
{
private:
	static const int DEFAULT_CAPACITY = 100;
	ItemType items[DEFAULT_CAPACITY]; // Array of list items 
	int itemCount; // Current count of list items 
	int maxItems; // Maximum capacity of the list 
public:
	ArrayList();
	// Copy constructor and destructor are supplied by compiler 
	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();
	/** @throw PrecondViolatedExcep if position < 1 or
	position > getLength(). */
	ItemType getEntry(int position) const;
	/** @throw PrecondViolatedExcep if position < 1 or
    position > getLength(). */
	void setEntry(int position, const ItemType& newEntry);
};

template<class ItemType>
inline ArrayList<ItemType>::ArrayList(): itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}

template< class ItemType>
bool ArrayList<ItemType>::isEmpty() const
{
	return itemCount == 0;
} // end isEmpty

template< class ItemType>
int ArrayList<ItemType>::getLength() const
{
	return itemCount;
} // end getLength

template< class ItemType>
bool ArrayList<ItemType>::insert(int newPosition,
	const ItemType& newEntry)
{
	bool ableToInsert = (newPosition >= 1) &&
		(newPosition <= itemCount + 1) &&
		(itemCount < maxItems);
	if (ableToInsert)
	{
		// Make room for new entry by shifting all entries at 
		// positions >= newPosition toward the end of the array 
		// (no shift if newPosition == itemCount + 1) 
		for (int pos = itemCount; pos >= newPosition; pos--)
			items[pos] = items[pos - 1];
		// Insert new entry 
		items[newPosition - 1] = newEntry;
		itemCount++; // Increase count of entries 
	} // end if 
	return ableToInsert;
} // end insert

template< class ItemType>
bool ArrayList<ItemType>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		// Remove entry by shifting all entries after the one at 
		 // position toward the beginning of the array 
		 // (no shift if position == itemCount) 
		for (int fromIndex = position, toIndex = fromIndex - 1;
			fromIndex < itemCount; fromIndex++, toIndex++)
			items[toIndex] = items[fromIndex];
		itemCount-- ; // Decrease count of entries 
	} // end if 
	return ableToRemove;
} // end remove

template< class ItemType>
void ArrayList<ItemType>::clear()
{
	itemCount = 0;
} // end clear 

template<class ItemType>
inline ItemType ArrayList<ItemType>::getEntry(int position) const
{
	return items[position - 1];
}

template<class ItemType>
inline void ArrayList<ItemType>::setEntry(int position, const ItemType& newEntry)
{
	items[position - 1] = newEntry;
}



