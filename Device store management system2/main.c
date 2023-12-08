#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Product
{
    char name[50];
    float price;
    int quantity;
    char description[100];
    char model[20];
    char color[20];
    int storage;
    int RAM;
    int exist;
};
typedef struct Product Product;

struct Category
{
    char name[20];
    int totalNumberOfProducts;
    Product *products;
    int exist;
};
typedef struct Category Category;

Category *allCategories[20]; // Assuming a maximum of 5 categories for simplicity
int categoryNumber = 0; // Track the number of categories

int validateProductQuantity2(char *ProductName, int requestedQuantity, int size, char *orderN[], int orderQuantity[])
{
    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {
            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if (strcmp(allCategories[i]->products[j].name, ProductName) == 0 && allCategories[i]->products[j].exist == 1)
                {
                    // Calculate the total quantity including both ordered and available quantities
                    int totalQuantity = allCategories[i]->products[j].quantity;

                    // Check if there are any pending orders for this product
                    for (int k = 0; k < size; k++)
                    {
                        if (strcmp(orderN[k], ProductName) == 0)
                        {
                            totalQuantity -= orderQuantity[k];
                        }
                    }

                    // Check if the requested quantity is valid
                    if (requestedQuantity <= totalQuantity)
                    {
                        return 1; // Valid quantity
                    }
                    else
                    {
                        return 0; // Invalid quantity
                    }
                }
            }
        }
    }
    return 0; // Product not found
}
//validate data int input
int getValidInt()
{
    int value;
    char buffer[20];

    while (1)
    {

        if (scanf("%d", &value) == 1)
        {
            // Check for extra characters in the input
            if (fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[0] != '\n')
            {
                printf("Invalid input. Please enter only numbers.\n");
                while (getchar() != '\n')
                    ; // Clear the input buffer
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("Invalid input. Please enter only numbers.\n");
            // Clear input buffer
            while (getchar() != '\n')
                ;
        }
    }
    return value;
}
// Function to validate float input
float getValidFloat()
{
    float value;
    char buffer[20];

    while (1)
    {

        if (scanf("%f", &value) == 1)
        {
            // Check for extra characters in the input
            if (fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[0] != '\n')
            {
                printf("Invalid input. Please enter numbers.\n");
                while (getchar() != '\n')
                    ; // Clear the input buffer
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("Invalid input. Please enter only numbers.\n");
            // Clear input buffer
            while (getchar() != '\n')
                ;
        }
    }
    return value;
}
// validate integer or float input
float getValidFloatOrInt()
{
    float value;
    char buffer[20];

    while (1)
    {
        if (scanf("%f", &value) == 1)
        {
            // Check for extra characters in the input
            if (fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[0] != '\n')
            {
                printf("Invalid input. Please enter only numbers.\n");
                while (getchar() != '\n')
                    ; // Clear the input buffer
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("Invalid input. Please enter only numbers.\n");
            // Clear input buffer
            while (getchar() != '\n')
                ;
        }
    }

    return value;
}
//displayDataUpdateFormat
void displayDataUpdateFormat()
{

    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {
            printf("Category Name: %s\n", allCategories[i]->name);
            printf("Total Number Of Products: %d\n", allCategories[i]->totalNumberOfProducts);
            printf("%-5s  %-15s  %-10s  %-15s %-10s  %-10s  %-10s\n", "Num", "Name", "Price", "Color", "Quantity", "RAM", "Storage");

            int productIndex = 1;
            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if (allCategories[i]->products[j].exist == 1)
                {
                    printf("%-5d  %-15s  %-10.2f  %-15s %-10d  %-10d  %-10d\n", productIndex, allCategories[i]->products[j].name,
                           allCategories[i]->products[j].price, allCategories[i]->products[j].color,allCategories[i]->products[j].quantity,allCategories[i]->products[j].RAM,
                           allCategories[i]->products[j].storage);
                    productIndex++;
                }
            }
            printf("****************************************************************************************************************************************\n");
        }
    }

}
//display data briefly
void displayDataBriefly()
{
    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {
            printf("Category Name: %s\n", allCategories[i]->name);
            printf("%-5s  %-15s  %-15s  %-10s\n", "Num", "Name", "Price", "Quantity");

            int productIndex = 1;
            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if (allCategories[i]->products[j].exist == 1)
                {
                    printf("%-5d  %-15s  %.2f         %-10d\n", productIndex, allCategories[i]->products[j].name,
                           allCategories[i]->products[j].price, allCategories[i]->products[j].quantity);
                    productIndex++;
                }
            }
            printf("****************************************************************************************************************************************\n");
        }
    }
}
//ckeck category name
int checkCategoryName(char *categoryName)
{
    // Iterate through existing categories to check if categoryName already exists
    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1 && strcmp(allCategories[i]->name, categoryName) == 0)
        {
            return 0; // Category with the same name already exists
        }
    }
    return 1; // Category name is unique
}
//add ctegory
void addCategory(Category *category)
{
    printf("Enter Category Name: ");
    gets(category->name);
    if(checkCategoryName(category->name))
    {
        printf("Enter Total Number Of Products:(if you don't need to add product now press 0): ");
        // scanf("%d", &category->totalNumberOfProducts);
        category->totalNumberOfProducts = getValidInt();
        // Allocate memory for products based on the total number of products
        category->products = (Product *)malloc(category->totalNumberOfProducts * sizeof(Product));
        // Initialize product details (you may want to add user input for each product)
        for (int i = 0; i < category->totalNumberOfProducts; i++)
        {

            // You can add more user input prompts here for product details
            printf("Enter Product Name for Product %d: ", i + 1);
            gets(category->products[i].name);
            printf("Enter Product Price for Product %d: ", i + 1);
            category->products[i].price = getValidFloatOrInt();
            printf("Enter Product Color for Product %d: ", i + 1);
            gets(category->products[i].color);
            printf("Enter Product quantity for Product %d: ", i + 1);
            category->products[i].quantity = getValidInt();
            printf("Enter Product RAM for Product %d: ", i + 1);
            category->products[i].RAM = getValidInt();
            printf("Enter Product storage for Product %d: ", i + 1);
            category->products[i].storage = getValidInt();
            category->products[i].exist=1;
            int existingIndex = areProductExist(&category->products[i], category);

            if (existingIndex >1)
            {
                // Duplicated product found
                printf("This product already exists in category %s. Product not added.\n", category->name);
                // Decrement totalNumberOfProducts as the product is not added
                category->totalNumberOfProducts--;
                i--; // Re-enter details for the current product
            }
            else
            {
                printf("********************************************************************************************\n");
            }
        }


        // Add the new category to the store
        // category->exist=1;
        allCategories[categoryNumber] = category;
        allCategories[categoryNumber]->exist=1;
        categoryNumber++;
        printf("Category Added Successfully\n");

    }
    else
    {

        printf("This category already exist\n");
    }




}

//validate in addcategory function
int areProductExist(Product *newProduct, Category *category)
{
    int counterExist=0;
    for (int j = 0; j < category->totalNumberOfProducts; j++)
    {
        if (category->products[j].exist)
        {
            if (strcmp(category->products[j].name, newProduct->name) == 0 &&
                    category->products[j].price == newProduct->price &&
                    strcmp(category->products[j].color, newProduct->color) == 0 &&
                    category->products[j].RAM == newProduct->RAM &&
                    category->products[j].storage == newProduct->storage)
            {
                counterExist++;
                // Duplicated product found
            }
        }
    }
    // No existing product found
    return counterExist;
}
//delete category
int deleteCategory(char *categoryName)
{

    for(int i=0; i<categoryNumber; i++)
    {
        if(strcmp(allCategories[i]->name,categoryName)==0)
        {

            allCategories[i]->exist=0;
            return i;

        }

    }

    return -1;
}
//search category by name
int searchCategoryByName(char *catName)
{

    for(int i=0; i<categoryNumber; i++)
    {
        if(strcmp(allCategories[i]->name,catName)==0 && allCategories[i]->exist==1)
        {

            return i;

        }

    }

    return -1;
}
//search by product name in all shop
int searchProductByName(char *productName)
{
    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {

            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if(strcmp(allCategories[i]->products[j].name,productName)==0 && allCategories[i]->products[j].exist==1)
                {
                    return j;

                }

            }

        }
    }

    return -1;
}
//getProductPrice
float getProductPrice(char *orderProductName)
{


    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {

            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if(strcmp(allCategories[i]->products[j].name,orderProductName)==0 && allCategories[i]->products[j].exist==1)
                {


                    return allCategories[i]->products[j].price;

                }
            }

        }
    }

    return 0;
}
//decrease Quantity
void decreaseQuantity(int Orderquantity, char *orderProductName)
{
    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {
            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if (strcmp(allCategories[i]->products[j].name, orderProductName) == 0 && allCategories[i]->products[j].exist == 1)
                {
                    // Print statements for debugging


                    // Check if quantity is sufficient before decrementing
                    if (allCategories[i]->products[j].quantity >= Orderquantity)
                    {
                        allCategories[i]->products[j].quantity -= Orderquantity;

                        // Print statements for debugging


                        // Break out of loops since the product is found and updated
                        return;
                    }
                    else
                    {
                        // Handle insufficient quantity case (optional)
                        printf("Insufficient quantity available for %s\n", orderProductName);
                        return;
                    }
                }
            }
        }
    }

    // If execution reaches here, the product was not found
    printf("Product %s not found\n", orderProductName);
}
//increaseQuantity
int increaseQuantity(int quantity, char *ProductName)
{
    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {
            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if (strcmp(allCategories[i]->products[j].name, ProductName) == 0 && allCategories[i]->products[j].exist == 1)
                {


                    allCategories[i]->products[j].quantity += quantity;

                    return 1 ;

                }
            }
        }
    }


    return 0;
}
//validate Product Quantity
int validateProductQuantity(char *ProductName,int quantityP)
{

    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {

            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if(strcmp(allCategories[i]->products[j].name,ProductName)==0 && allCategories[i]->products[j].exist==1)
                {

                    if (quantityP <= allCategories[i]->products[j].quantity )
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }

                }
            }

        }
    }
    return 1;
}
//add product to specific category
void addProduct(int index)
{
    char check='n';
    allCategories[index]->totalNumberOfProducts++;
    allCategories[index]->products =
        realloc(allCategories[index]->products, allCategories[index]->totalNumberOfProducts * sizeof(Product));

    int i = allCategories[index]->totalNumberOfProducts - 1;

    printf("Enter Product Name for Product %d: ", i + 1);
    scanf("%s", allCategories[index]->products[i].name);
    printf("Enter Product Price for Product %d: ", i + 1);
    allCategories[index]->products[i].price = getValidFloatOrInt();
    printf("Enter Product Color for Product %d: ", i + 1);
    scanf("%s", allCategories[index]->products[i].color);
    printf("Enter Product quantity for Product %d: ", i + 1);
    allCategories[index]->products[i].quantity = getValidInt();
    printf("Enter Product RAM for Product %d: ", i + 1);
    allCategories[index]->products[i].RAM = getValidInt();
    printf("Enter Product storage for Product %d: ", i + 1);
    allCategories[index]->products[i].storage = getValidInt();

    // Add the new product to the category
    allCategories[index]->products[i].exist = 1;

    // Check if the product already exists
    int existingIndex = areProductsEqual(&allCategories[index]->products[i], index);
    if (existingIndex != -1)
    {
        // Product already exists, validate and deallocate if necessary
        if (!validateProduct(&allCategories[index]->products[i], index, i))
        {
            // Validation failed, deallocate the newly added product
            allCategories[index]->products[i].exist = 0;
            allCategories[index]->totalNumberOfProducts--;
            printf("This product is already exist, are you need to increase its quantity(Y/N)?  \n");
            scanf(" %c",&check);
            if (check == 'Y' || check == 'y')
            {
                if(increaseQuantity(allCategories[index]->products[i].quantity,
                                       allCategories[index]->products[i].name))
                {
                    printf("Product Updated Quantity\n");
                }
                else
                {
                    printf("can't able to update product quantity\n");
                }
            }
            else
            {
                printf("Product not added\n");
            }

        }
        else
        {
            printf("Product Added Successfully\n");
        }
    }
    else
    {
        printf("Product Added Successfully\n");
    }
}
//Compare the new product with existing products
int validateProduct(Product *newProduct, int categoryIndex, int newProductIndex)
{
    for (int j = 0; j < allCategories[categoryIndex]->totalNumberOfProducts; j++)
    {
        if (j != newProductIndex && allCategories[categoryIndex]->products[j].exist)
        {

            if (strcmp(allCategories[categoryIndex]->products[j].name, newProduct->name) == 0 &&
                    allCategories[categoryIndex]->products[j].price == newProduct->price &&
                    strcmp(allCategories[categoryIndex]->products[j].color, newProduct->color) == 0 &&
                    allCategories[categoryIndex]->products[j].RAM == newProduct->RAM &&
                    allCategories[categoryIndex]->products[j].storage == newProduct->storage)
            {
                return 0;
            }
        }
    }

    return 1;
}
//get duplicated index to remove object
int areProductsEqual(Product *newProduct, int categoryIndex)
{
    for (int j = 0; j < allCategories[categoryIndex]->totalNumberOfProducts; j++)
    {
        if (allCategories[categoryIndex]->products[j].exist)
        {
            if (strcmp(allCategories[categoryIndex]->products[j].name, newProduct->name) == 0 &&
                    allCategories[categoryIndex]->products[j].price == newProduct->price &&
                    strcmp(allCategories[categoryIndex]->products[j].color, newProduct->color) == 0 &&
                    allCategories[categoryIndex]->products[j].RAM == newProduct->RAM &&
                    allCategories[categoryIndex]->products[j].storage == newProduct->storage)
            {
                return j;  // Return the index of the existing product
            }
        }
    }
    // No existing product found
    return -1;
}
//delete product in specific category
void deleteProduct(int categoryIndex, char *productName)
{
    int product_count = allCategories[categoryIndex]->totalNumberOfProducts;

    for (int i = 0; i < product_count; i++)
    {
        if (allCategories[categoryIndex]->products[i].exist == 1 && strcmp(allCategories[categoryIndex]->products[i].name, productName) == 0)
        {
            // Product found, mark it as not existing
            allCategories[categoryIndex]->products[i].exist = 0;

            // Shift the remaining products to fill the gap
            for (int j = i; j < product_count - 1; j++)
            {
                allCategories[categoryIndex]->products[j] = allCategories[categoryIndex]->products[j + 1];
            }

            // Mark the last product as not existing
            allCategories[categoryIndex]->products[product_count - 1].exist = 0;

            // Update the total number of products
            allCategories[categoryIndex]->totalNumberOfProducts--;

            printf("Product deleted successfully\n");
            return;
        }
    }

    printf("Product not found\n");
}
//change product category
int moveProduct(char *selectedProductName,int positionOldCat,int positionNewCat)
{
    int product_count = allCategories[positionOldCat]->totalNumberOfProducts;

    for (int i = 0; i < product_count; i++)
    {
        if (allCategories[positionOldCat]->products[i].exist == 1 && strcmp(allCategories[positionOldCat]->products[i].name, selectedProductName) == 0)
        {
            // Product found in the old category, now move it to the new category

            // Update totalNumberOfProducts of the new category
            allCategories[positionNewCat]->totalNumberOfProducts++;

            // Allocate space in the new category
            allCategories[positionNewCat]->products =
                realloc(allCategories[positionNewCat]->products, allCategories[positionNewCat]->totalNumberOfProducts * sizeof(Product));

            // Find the index in the new category
            int newPos = allCategories[positionNewCat]->totalNumberOfProducts - 1;

            // Copy product details to the new category
            memcpy(&allCategories[positionNewCat]->products[newPos], &allCategories[positionOldCat]->products[i], sizeof(Product));

            //  shifting the products in the old category array after moving one product to the new category
            for (int j = i; j < allCategories[positionOldCat]->totalNumberOfProducts - 1; j++)
            {
                allCategories[positionOldCat]->products[j] = allCategories[positionOldCat]->products[j + 1];
            }

            // Mark the last product as not existing in the old category
            allCategories[positionOldCat]->products[allCategories[positionOldCat]->totalNumberOfProducts - 1].exist = 0;

            // Update totalNumberOfProducts of the old category
            allCategories[positionOldCat]->totalNumberOfProducts--;

            return 1; // Product moved successfully
        }
    }

    return 0; // Product not found in the old category

}
//make order
void makeOrder()
{
    displayDataUpdateFormat();
    char saledProductName[20];
    int quantityProduct;
    int isAvailableQuantity = 0;
    int *orderQuantity = NULL;
    char **orderN = NULL;
    float *orderPrice = NULL;
    int size = 0;
    int c = 0;
    char again = 'n';
    char confirm = 'n';
    char check = 'n';
    float totalOrderPrice = 0;

    while (c !=-1)
    {
        printf("Product Name\n");
        scanf_s("%s",saledProductName);
        printf("Quantity sold\n");
        scanf("%d", &quantityProduct);

        if (searchProductByName(saledProductName) != -1)
        {

            printf("Product Exist\n");

            isAvailableQuantity = validateProductQuantity2(saledProductName, quantityProduct, size, orderN, orderQuantity);

            if (isAvailableQuantity == 1 && quantityProduct>0 )
            {
                printf("This quantity is available\n");
                size++;

                // Allocate memory for orderQuantity, orderN, and orderPrice
                orderQuantity = (int *)realloc(orderQuantity, size * sizeof(int));
                orderN = (char **)realloc(orderN, size * sizeof(char *));
                orderPrice = (float *)realloc(orderPrice, size * sizeof(float));

                // Allocate memory for the product name and copy the name
                orderN[size - 1] = (char *)malloc(strlen(saledProductName) + 1);
                strcpy(orderN[size - 1], saledProductName);

                // Assign quantity and price to orderQuantity and orderPrice
                orderQuantity[size - 1] = quantityProduct;
                orderPrice[size - 1] = getProductPrice(saledProductName);
            }
              if(isAvailableQuantity ==0 || quantityProduct<=0 )
                {
                    printf("This quantity is not available\n");
                }



        }
        else{ printf("Product Not Exist\n");}

        printf("Are you need to end order?(Y/N)\n");
        scanf(" %c", &check);

        if (check == 'Y' ||check == 'y')
        {
            c = -1;

        }
    }
    if(size>0)
    {
        printf("Your order is: \n");
        printf("%-5s  %-15s  %-15s  %-10s\n", "Num", "Product Name", "Quantity", "Price");
        for (int i = 0; i < size; i++)
        {
            totalOrderPrice += orderPrice[i] * orderQuantity[i];
            printf(" %-5d %-15s %-15d %-10f\n", i + 1, orderN[i], orderQuantity[i], orderPrice[i]);
        }
        printf("Total Order Price: %f $\n", totalOrderPrice);
        printf("Confirm This Order?(Y/N)\n");
        scanf(" %c", &confirm);
        if (confirm == 'Y' || confirm == 'y')
        {
            for (int i = 0; i < size; i++)
            {

                decreaseQuantity(orderQuantity[i], orderN[i]);
                free(orderN[i]); // Free memory for each product name
            }

            printf("Congratulations the order done successfully\n");
        }
        else
        {
            printf("The order is Canceled\n");
        }

        printf("Shop After Order \n");
        displayDataUpdateFormat();


    }
    // Free memory for arrays
    free(orderQuantity);
    free(orderN);
    free(orderPrice);
}
//edit product quantity
int editProductQuantity(char *ProductName,int udatedQuantity)
{

    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {

            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if(strcmp(allCategories[i]->products[j].name,ProductName)==0 && allCategories[i]->products[j].exist==1)
                {

                    allCategories[i]->products[j].quantity =udatedQuantity;
                    return 1;
                }
            }

        }
    }
    return 0;

}
//Get Product Info
void GetProductInfo(char *productName)
{
    int productIndex = 1;

    printf("%-5s  %-15s  %-10s  %-15s  %-10s    %-10s  %-10s  %-10s\n",
           "Num", "Name", "Price", "Quantity", "Category", "Color", "RAM", "Storage");

    for (int i = 0; i < categoryNumber; i++)
    {
        if (allCategories[i]->exist == 1)
        {
            for (int j = 0; j < allCategories[i]->totalNumberOfProducts; j++)
            {
                if (strcmp(allCategories[i]->products[j].name, productName) == 0 &&
                    allCategories[i]->products[j].exist == 1)
                {

                    printf("%-5d  %-15s  %-10.2f  %-15d  %-15s  %-10s  %-10d  %-10d\n",
                           productIndex, allCategories[i]->products[j].name,
                           allCategories[i]->products[j].price, allCategories[i]->products[j].quantity,
                           allCategories[i]->name, allCategories[i]->products[j].color,
                           allCategories[i]->products[j].RAM, allCategories[i]->products[j].storage);

                    productIndex++;
                }
            }
        }
    }
}




void displayHome()
{
    int choice = 0;
    int selectedOption = 1;

    char *menu[] = {"Add Category", "Delete Category","Display Categories and products", "Search About Product",
                    "Add Product", "Delete Product", "Update Product Quantity",
                    "Edit Product Category", "Start Order", "Exit"
                   };
    int menu_len = sizeof(menu) / sizeof(menu[0]);

    while (choice != 10)
    {
        system("cls"); // Clear the screen

        for (int i = 0; i < menu_len; i++)
        {
            if (i == selectedOption - 1)
            {
                SetColor(16); // Set color for the selected option
                printf("*** ");
            }
            else
            {
                SetColor(15); // Set color for unselected options
                printf("  ");
            }

            printf("%d- %s \n", i + 1, menu[i]);
        }

        // Handle user input outside the loop that prints the menu
        char ch = getch();
        if (ch == -32) // Arrow key is pressed
        {
            ch = getch(); // Get the extended code
            if (ch == 72) // Up arrow
            {
                selectedOption--;
                if (selectedOption < 1)
                    selectedOption = menu_len;
            }
            else if (ch == 80)   // Down arrow
            {
                selectedOption++;
                if (selectedOption > menu_len)
                    selectedOption = 1;
            }
        }

        // If the "Add Category" option is selected, call the addCategory function
        if (selectedOption == 1 && ch == 13) // Enter key
        {
            Category *newCategory = (Category *)malloc(sizeof(Category));
            addCategory(newCategory);
            printf("\nPress any key to continue...");
            getch();
        }
        if (selectedOption == 2 && ch == 13) // Enter key to delete category
        {
            if(categoryNumber==0)
            {
                printf("Store currently don't contain any categories \n");
            }
            else
            {
                displayDataUpdateFormat();
                char deletedCategoryName[20];
                printf("Enter Category Name To Delete: ");
                scanf_s("%s",deletedCategoryName);

                if (deleteCategory(deletedCategoryName)>=0)
                {
                    printf("Category Deleted Successfully\n");
                }
                else
                {
                    printf("Sorry Can't Delete Be Sure From Category Name\n");
                }
            }
            printf("\nPress any key to continue...");
            getch();

        }
        if (selectedOption == 3 && ch == 13) // Enter key for "Display category and its products"
        {
            if(categoryNumber==0)
            {
                printf("Store currently don't contain any categories \n");
            }
            else
            {
                displayDataUpdateFormat();
            }
            printf("\nPress any key to continue...");
            getch(); // Wait for a key press before returning to the main menu
        }
        if (selectedOption == 5 && ch == 13) // Enter key for add product in specific category
        {
            if(categoryNumber==0)
            {
                printf("Store currently don't contain any categories \n");
            }
            else
            {
                displayDataUpdateFormat();
                printf("Please Enter Category Name of the Product: ");
                char catName[20];
                gets(catName);
                if(searchCategoryByName(catName)>=0)
                {
                    addProduct(searchCategoryByName(catName));
                }
                else
                {

                    printf("Sorry can't add your Product be sure with category name");
                }
            }
            printf("\nPress any key to continue...");
            getch(); // Wait for a key press before returning to the main menu
        }


        ////////////search about product

        if (selectedOption == 4 && ch == 13) // Enter key for add product in specific category
        {

            if(categoryNumber==0)
            {
                printf("Store currently don't contain any categories \n");
            }
            else
            {
                char productName[20];
                printf("Enter product name: ");
                gets(productName);
                if(searchProductByName(productName)!=-1)
                {
                    GetProductInfo(productName);
                }
                else
                {
                    printf("Sorry Product Not Exist \n");
                }

            }
            printf("\nPress any key to continue...");
            getch(); // Wait for a key press before returning to the main menu
        }

        if (selectedOption == 6 && ch == 13) // Enter key for delete product in specific category
        {
            if(categoryNumber==0)
            {
                printf("Store currently don't contain any categories \n");
            }
            else
            {
                printf("Please Enter Category Name: ");
                char catName[20];
                gets(catName);
                if(searchCategoryByName(catName)>=0)
                {
                    printf("Category exist please enter product name: ");
                    char productName[20];
                    gets(productName);
                    deleteProduct(searchCategoryByName(catName),productName);
                }
                else
                {
                    printf("Sorry can't delete your Product be sure with category name");
                }
            }
            printf("\nPress any key to continue...");
            getch(); // Wait for a key press before returning to the main menu
        }

        /////////////// Enter key for Increase Product Quantity

        if (selectedOption == 7 && ch == 13) // Enter key for delete product in specific category
        {
            if(categoryNumber==0)
            {
                printf("Store currently don't contain any categories \n");
            }
            else
            {
                char productName[20];
                int updateQuantity=0;
                displayDataUpdateFormat();
                printf("Enter Name of Product \n");
                gets(productName);
                printf("Enter Updated Quantity \n");
                scanf("%d",&updateQuantity);
                if(editProductQuantity(productName,updateQuantity))
                {
                    printf("Product Quantity Updated Successfully \n");
                }
                else
                {
                    printf("Sorry Can't Update Product Not Exist \n");
                }
                // increaseProductQuantity();
            }
            printf("\nPress any key to continue...");
            getch(); // Wait for a key press before returning to the main menu
        }



        if (selectedOption == 8 && ch == 13)  // Enter key for Edit Product Category
        {
            if (categoryNumber == 0)
            {
                printf("Store currently doesn't contain any categories\n");
            }
            else
            {
                displayDataUpdateFormat();
                char moveProductName[20];
                char oldCatName[20];
                char newCatName[20];

                printf("Enter Product Name: ");
                gets(moveProductName);
                if(searchProductByName(moveProductName)>=0)
                {
                    printf("Enter Old Category Name: ");
                    gets(oldCatName);

                    int oldCategoryIndex = searchCategoryByName(oldCatName);

                    if (oldCategoryIndex >= 0)
                    {


                        printf("Enter New Category Name: ");
                        gets(newCatName);

                        int newCategoryIndex = searchCategoryByName(newCatName);

                        if (newCategoryIndex >= 0)
                        {
                            int isMoved = moveProduct(moveProductName, oldCategoryIndex, newCategoryIndex);

                            if (isMoved)
                            {
                                printf("Product Moved Successfully\n");
                            }
                            else
                            {
                                printf("Product Failed to Move\n");
                            }
                        }
                        else
                        {
                            printf("New Category Doesn't Exist\n");
                        }
                    }
                    else
                    {
                        printf("Old Category Doesn't Exist\n");
                    }
                }
                else
                {
                    printf("Product Doesn't Exist\n");
                }
            }
            printf("\nPress any key to continue...");
            getch(); // Wait for a key press before returning to the main menu
        }
        if (selectedOption == 9 && ch == 13)
        {
            if(categoryNumber==0)
            {
                printf("Store currently don't contain any categories \n");
            }
            else
            {
                makeOrder();
            }
            printf("\nPress any key to continue...");
            getch(); // Wait for a key press before returning to the main menu
        }
         if (selectedOption == 10 && ch == 13)
        {
             system("cls");
             SetColor(15);
             printf("\n\n\n\n\n\n\n\n\t\t\t\tHave a nice time Beye!\n\t\t\t\tDevice Store Management System!");
            Sleep(INFINITE);

        }


    }
}

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

int main()
{
    displayHome();
    return 0;
}
