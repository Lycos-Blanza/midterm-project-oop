``**Validations:**``

1. Category Validation:
   - The user is prompted to input a valid category when adding an item. Available categories are "Clothing", "Electronics", and "Entertainment".
   - If the entered category is not one of the available categories, an error message is shown, and the user is asked to re-enter a valid category.

2. ID Validation:
   - When adding a new item, the program checks whether the item ID already exists in the inventory.
   - If the entered ID already exists, the user is prompted to enter a different ID.

3. Field Validation for Update:
   - When updating an item, the program validates that the field to be updated is either "Quantity" or "Price".
   - If an invalid field is entered, the user is asked to re-enter the correct field.

4. Item Presence Validation:
   - Before performing operations like updating, removing, or searching for an item, the program checks if there are items in the inventory.
   - If no items are present, a message is displayed to inform the user that there are no items in the inventory.

5. Search Validation:
   - When searching for an item by its ID, if the item is not found in the inventory, a message is displayed stating that no item with the entered ID exists.

6. Sorting Option Validation:
   - When sorting items, the program ensures that the user enters a valid sorting option (1 for Quantity, 2 for Price).
   - If an invalid sorting option is entered, the user is prompted to re-enter a valid option.

7. Sorting Order Validation:
   - After selecting a sorting option, the user must choose between ascending (1) or descending (2) order.
   - If an invalid order is selected, the user is prompted to enter a valid option between 1 and 2.

8. Low Stock Display:
   - Before displaying low-stock items, the program checks if there are any items in the inventory.
   - If no items exist, it informs the user that the inventory is empty.

``**Functions Used**``

1. toLowerString(const string str)
2. Display() const override (Clothing, Electronics, Entertainment classes)
3. GetCategory() const override (Clothing, Electronics, Entertainment classes)
4. UpdateQuantity(int newQuantity)
5. UpdatePrice(double newPrice)
6. getID() const
7. getName() const
8. getQuantity() const
9. getPrice() const
10. CreateItem(const string category, const string id, const string name, int quantity, double price)
11. AddItem(Item* item)
12. IDExists(const string id) const
13. UpdateItem(const string id, const string field, double newValue)
14. RemoveItem(string id)
15. DisplayItemsByCategory(const string category) const
16. SuggestAvailableCategories() const
17. DisplayAllItems() const
18. SearchItem(string id) const
19. SortItemsByQuantity()
20. SortItemsByPrice()
21. SortItemsByQuantityDescending()
22. SortItemsByPriceDescending()
23. DisplayLowStockItems(int limit) const
24. MainMenu()
