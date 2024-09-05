:- consult('data.pl').
:- dynamic item/3.
:- dynamic alternative/2.
:- dynamic boycott_company/2.
## predicates are dynamic, meaning their definitions can be added, removed, or updated during runtime.

% This predicate retrieves a list of orders for a given customer.
list_orders(CustomerUsername, Orders) :-
    customer(CustomerID, CustomerUsername),
    find_all_orders(CustomerID, Orders).

% This predicate counts the number of orders for a given customer.
countOrdersOfCustomer(CustomerUsername, Count) :-
    customer(CustomerID, CustomerUsername),
    find_all_order_ids(CustomerID, OrderIDs),
    count_items(OrderIDs, Count).

% This predicate retrieves the items in a specific order for a given customer.
getItemsInOrderById(CustomerUsername, OrderID, Items) :-
    customer(CustomerID, CustomerUsername),
    order(CustomerID, OrderID, Items).

% This predicate finds all orders associated with a given CustomerID.
find_all_orders(CustomerID, Orders) :-
    findall(order(CustomerID, OrderID, Items), order(CustomerID, OrderID, Items), Orders).

% This predicate finds all order IDs associated with a given CustomerID.
find_all_order_ids(CustomerID, OrderIDs) :-
    findall(OrderID, order(CustomerID, OrderID, _), OrderIDs).

% This predicate counts the items in a list.
count_items([], 0).
count_items([_|Rest], Count) :-
    count_items(Rest, SubCount),
    Count is SubCount + 1.

count_list([], 0).
count_list([Head | Tail], Count) :-
    count_list(Tail, TempCount),
    Count is TempCount + 1.

getNumOfItems(CustomerName, OrderID, Count) :-
    customer(CustID, CustomerName), 
    order(CustID, OrderID, Items),
    count_list(Items, Count).

% Main predicate to calculate the total price of an order.
calcPriceOfOrder(CustomerName, OrderID, TotalPrice) :-
    customer(CustID, CustomerName), 
    order(CustID, OrderID, Items),
    totalPrice(Items, 0, TotalPrice).

% Helper predicate to calculate the total price of items in an order (recursive).
totalPrice([], Acc, Acc).
totalPrice([Item | Tail], Acc0, TotalPrice) :-
    item(Item, _, Price),
    Acc1 is Acc0 + Price,
    totalPrice(Tail, Acc1, TotalPrice).

% Helper predicate to find all alternatives for an item.
find_alternatives(Item, Alternatives) :-
    findall(Alt, (alternative(Item, Alt)), Alternatives).

% Predicate to check if an item is boycotted.
isBoycott(Item) :-
    alternative(Item, _); % Directly boycotted
    (find_alternatives(Item, Alternatives), \+ Alternatives = []). % Check if there are alternatives







% Predicates for Operations
% Helper predicate to get the price of an item or its alternative
get_price(Item, Price) :- # (underscore _ ):هذا المتغير المجهول يطابق أي قيمة، لكننا لن نستخدمه، لذلك لا نعطيه اسمًا.
    item(Item, _, Price), !.##  ! is the cut operator, which prevents backtracking past this point if the item is found.
get_price(Item, Price) :-
    alternative(Item, AltItem),
    item(AltItem, _, Price).

% Recursive predicate to collect alternative items
collect_alternatives([], []).
collect_alternatives([Item|RestItems], [AltItem|RestAltItems]) :-
    (alternative(Item, AltItem) -> true; AltItem = Item),
    collect_alternatives(RestItems, RestAltItems).

% Recursive predicate to collect prices of items
collect_prices([], 0).
collect_prices([Item|RestItems], TotalPrice) :-
    get_price(Item, Price),
    collect_prices(RestItems, RestTotalPrice),
    TotalPrice is Price + RestTotalPrice.

% Predicate to calculate the total price of an order after replacing boycott items
calcPriceAfterReplacingBoycottItemsFromAnOrder(Username, OrderID, NewList, TotalPrice) :-
    customer(CustomerID, Username),
    order(CustomerID, OrderID, ItemsList),
    collect_alternatives(ItemsList, NewList),
    collect_prices(NewList, TotalPrice).



% Define a predicate to retrieve the price for a given item in a given location.
price_in_location(Item, Location, Price) :-
    (Location \= '-' -> item_price(Item, Price); item(Item, _, Price)).

% Predicate to calculate the difference in price between item and alternative.
getTheDifferenceInPriceBetweenItemAndAlternative(Item, Alternative, DiffPrice) :-
    (alternative(Item, AltItem) ->
        price_in_location(Item, _, ItemPrice),
        price_in_location(AltItem, _, AltPrice),
        Alternative = AltItem,
        DiffPrice is ItemPrice - AltPrice
    ; DiffPrice = 'No alternative found'
    ).
% Bonus%
% Predicate to add an item.
add_item(Item, Location, Price) :-
    assertz(item(Item, Location, Price)).

% Predicate to remove an item.
remove_item(Item, Location, Price) :-
    retract(item(Item, Location, Price)).

% Predicate to add an alternative.
add_alternative(Item, Alternative) :-
    assertz(alternative(Item, Alternative)).

% Predicate to remove an alternative.
remove_alternative(Item, Alternative) :-
    retract(alternative(Item, Alternative)).

% Predicate to add a new boycott company.
add_boycott_company(Company, Reason) :-
    assertz(boycott_company(Company, Reason)).

% Predicate to remove a boycott company.
remove_boycott_company(Company, Reason) :-
    retract(boycott_company(Company, Reason)).

% This predicate retrieves a list of orders for a given customer.
list_orders(CustomerUsername, Orders) :-
    customer(CustomerID, CustomerUsername),
    find_all_orders(CustomerID, Orders).

% This predicate counts the number of orders for a given customer.
countOrdersOfCustomer(CustomerUsername, Count) :-
    customer(CustomerID, CustomerUsername),
    find_all_order_ids(CustomerID, OrderIDs),
    count_items(OrderIDs, Count).

% This predicate retrieves the items in a specific order for a given customer.
getItemsInOrderById(CustomerUsername, OrderID, Items) :-
    customer(CustomerID, CustomerUsername),
    order(CustomerID, OrderID, Items).

% This predicate finds all orders associated with a given CustomerID.
find_all_orders(CustomerID, Orders) :-
    findall(order(CustomerID, OrderID, Items), order(CustomerID, OrderID, Items), Orders).

% This predicate finds all order IDs associated with a given CustomerID.
find_all_order_ids(CustomerID, OrderIDs) :-
    findall(OrderID, order(CustomerID, OrderID, _), OrderIDs).

% This predicate counts the items in a list.
count_items([], 0).
count_items([_|Rest], Count) :-
    count_items(Rest, SubCount),
    Count is SubCount + 1.

% Predicate to provide justification for boycotting an item or company.
justification(Item, Justification) :-
    item(Item, Company, _),
    boycott_company(Company, CompanyJustification),
    format(atom(Justification), 'Boycott ~w: ~w', [Item, CompanyJustification]).

justification(Company, Justification) :-
    boycott_company(Company, Justification).

% Predicate to explain why to boycott a company or item.
whyToBoycott(CompanyOrItem, Justification) :-
    justification(CompanyOrItem, Justification).

% Predicate to remove boycotted items from an order.
removeBoycottItemsFromAnOrder(Username, OrderID, NewList) :-
    customer(CustomerID, Username),
    order(CustomerID, OrderID, OrderItems),
    removeBoycottItems(OrderItems, NewList).

removeBoycottItems([], []).
removeBoycottItems([Item | Rest], NewList) :-
    \+ boycott_item(Item),
    removeBoycottItems(Rest, NewTail),
    append([Item], NewTail, NewList).

removeBoycottItems([_ | Rest], NewList) :-
    removeBoycottItems(Rest, NewList).

% Predicate to check if an item is from a boycotted manufacturer.
boycott_item(Item) :-
    item(Item, Manufacturer, _),
    boycott_company(Manufacturer, _).

% Predicate to replace boycotted items with alternatives in an order.
replaceBoycottItemsFromAnOrder(Username, OrderID, NewList) :-
    customer(CustomerID, Username),
    order(CustomerID, OrderID, OrderItems),
    replaceBoycottItems(OrderItems, NewList).

replaceBoycottItems([], []).
replaceBoycottItems([Item | Rest], NewList) :-
    ( \+ boycott_item(Item) ->
        append([Item], NewTail, NewList),
        replaceBoycottItems(Rest, NewTail)
    ;
        alternative(Item, Alternative),
        append([Alternative], NewTail, NewList),
        replaceBoycottItems(Rest, NewTail)
    ).

boycott_item(Item) :-
    item(Item, Manufacturer, _),
    boycott_company(Manufacturer, _).
