# Project Design Document

## Introduction

This web service is an easy-to-use platform for customers to order tacos online from their favorite tacos restaurant. It allows for customization of orders, viewing of menu items, and provides a quick, hassle-free ordering process.
This service aims to enhance the Tacos customer experience by offering a digital solution for easy and personalized Tacos ordering. It targets tacos restaurants that have a web site that handles online orders.

## Background/Context

This web service is developed to address the need for a quick and convenient way to order tacos. Many tacos restaurants may lack an efficient online ordering system, leading to longer wait times and limited customization for customers. This service aims to fill that gap by providing a user-friendly online platform where customers can easily customize and order their tacos, thereby improving the overall ordering experience and meeting the modern demands of convenience and efficiency.

## Stakeholders

Customers: 

    Individuals who will use the service for ordering tacos online. They are the primary users and beneficiaries of the service, seeking convenience, speed, and customization in their orders.

Tacos Restaurant Owners/Managers: 

    Business owners who will adopt this web service to offer online ordering to their customers. They are interested in increasing sales, improving customer satisfaction, and streamlining the ordering process.

## Functional Requirements

Menu Display and Customization:

    Display the current menu of tacos and related items.
    Allow customers to customize their tacos orders (choice of fillings, toppings, etc.).

Order Placement and Management:

    Facilitate easy addition of items to the order.
    Enable modification (add/remove items) on the order.

User Account Management:

    Allow users to create and manage accounts, storing information such as name, contact details ect.

Data Storage and Retrieval:

    Store order details, user information, and menu items in a database.

## Use Case Description

Viewing the Menu

    As a user, I want to view the complete menu of tacos, including details like meat and sauces. I can also add, modify and delete elements of the menu.

Customizing Tacos

    As a user, I want to customize tacos by selecting my preferred meat, and sauces. 

Viewing Nutritional Information

    As a user, I want to view the nutritional information of each ingredient.

Creating an Order

    As a user, I want to easily add tacos to my order, so that I can select multiple items from the menu for my meal.

Modifying the Order

    As a user, I want the ability to modify my order (add or remove items).

Account Management

    As a returning customer, I want to create and manage my account, storing my username, contact details, and order history (maybe having discounts)

Order History Review

    As a customer, I want to view my previous orders, so that I can reorder my favorites or use them as a reference for new orders.

## List Of Resources

Meat Resource

    Description: Contains detailed information about each Meat used in the tacos, including nutritional values.
    Functionality: Viewing meats and their nutritional information, adding, modifying and deleting them.

Sauce Resource

    Description: Contains detailed information about each sauce used in the tacos, including nutritional values.
    Functionality: Viewving sauces and their nutritional information, adding, modifying and deleting them.

Soda Resource

    Description: Contains detailed information about each soda including nutritional values.
    Functionality: Viewving soda and its nutritional information, adding, modifying and deleting them.

Tacos Resource

    Description: Contains detailed information about each tacos, including nutritional values.
    Functionality: Viewving tacos and their nutritional information, adding, modifying and deleting them.

Order Resource

    Description: This resource manages the creation and modification of customer orders. It allows users to add tacos to their order, customize them, and modify the order.
    Functionality: Adding tacos to an order, customizing orders, modifying orders (add/remove items), and deleting orders.


## List of End Points

Menu Resource Endpoints

    GET /menu

    Retrieves the full taco menu.
    Expected Response: JSON object with menu items.
    HTTP Status Code: 200 (OK).
    Error: 404 (Not Found) if menu is empty.
    POST /menu

    Adds a new item to the menu.
    Request Body: JSON object containing new menu item details.
    Expected Response: Confirmation message with added item details.
    HTTP Status Code: 201 (Created).
    Error: 400 (Bad Request) for invalid input.
    PUT /menu/{itemId}

    Updates a specific item in the menu.
    Request Parameters: itemId (ID of the item to update).
    Request Body: JSON object with updated item details.
    Expected Response: Confirmation message with updated item details.
    HTTP Status Code: 200 (OK).
    Error: 404 (Not Found) if item not found.
    DELETE /menu/{itemId}

    Deletes a specific item from the menu.
    Request Parameters: itemId (ID of the item to delete).
    Expected Response: Confirmation message of deletion.
    HTTP Status Code: 200 (OK).
    Error: 404 (Not Found) if item not found.

Meat Resource Endpoints

    Similar structure as Menu Resource Endpoints, with URLs like /meat, /meat/{meatId}, supporting GET, POST, PUT, DELETE methods.

Sauce Resource Endpoints

    Similar structure as Meat Resource Endpoints, with URLs like /sauce, /sauce/{sauceId}, supporting GET, POST, PUT, DELETE methods.

Soda Resource Endpoints

    Similar structure as Sauce Resource Endpoints, with URLs like /soda, /soda/{sodaId}, supporting GET, POST, PUT, DELETE methods.

Tacos Resource Endpoints

    Similar structure as Soda Resource Endpoints, with URLs like /tacos, /tacos/{tacoId}, supporting GET, POST, PUT, DELETE methods.

Order Resource Endpoints

    GET /order/{orderId}

    Retrieves a specific order.
    Request Parameters: orderId (ID of the order to retrieve).
    Expected Response: JSON object with order details.
    HTTP Status Code: 200 (OK).
    Error: 404 (Not Found) if order not found.
    POST /order

    Places a new order.
    Request Body: JSON object containing order details.
    Expected Response: Confirmation message with order details.
    HTTP Status Code: 201 (Created).
    Error: 400 (Bad Request) for invalid input.
    PUT /order/{orderId}

    Modifies an existing order.
    Request Parameters: orderId.
    Request Body: JSON object with updated order details.
    Expected Response: Confirmation message with updated order details.
    HTTP Status Code: 200 (OK).
    Error: 404 (Not Found) if order not found.
    DELETE /order/{orderId}

    Cancels an existing order.
    Request Parameters: orderId.
    Expected Response: Confirmation message of cancellation.
    HTTP Status Code: 200 (OK).
    Error: 404 (Not Found) if order not found.


## UML Diagrams

See UML_diagram.png