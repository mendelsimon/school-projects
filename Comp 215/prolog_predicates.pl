member1(N, [N | _]) :- !. % If the list begins with N, then N is a member.
member1(N, [_ | T]) :- member1(N, T).


% rest_list is the same as member1, but the result is printed or stored in a variable
rest_list(N, L) :- L = [N | _], write(L), !.
rest_list(N, [_ | T]) :- rest_list(N, T).

%alternatively, storing the result in a variable:
rest_list(N, L, R) :- L = [N | _], R = L, !.
rest_list(N, [_ | T], R) :- rest_list(N, T, R).


append1([], R, R). % With all the elements of the first list removed, it should be identical to the second list.
append1([H1 | T1], L2, [H1 | TR]) :- 
    append1(T1, L2, TR).


zip([], _, []) :- !. % Stop if the first list is empty
zip(_, [], []) :- !. % or if the second list is empty.
zip([H1 | T1], [H2 | T2], [H1-H2 | TR]) :-
    zip(T1, T2, TR).


flatten([], []). 
flatten([H | T], [H | TR]) :- 
    \+is_list(H), !,
    flatten(T, TR).

flatten([H | T], R) :- 
    is_list(H),
    flatten(H, FH),
    pop(FH, R, TR), % pop/3 is defined below
    flatten(T, TR).


% pop(I, L, R) has R equal to L with the elements of I removed from the front
% e.g. I=[1, 2], L=[1, 2, 3, 4, 5], R=[3, 4, 5]
pop([], L, R) :- R = L.
pop([TOP | TI], [TOP | TL], R) :-
    pop(TI, TL, R).


% Check if a variable is a list.
is_list([]).
is_list([_|_]).

% This predicate returns true if all the example test cases in the assignment pass.
tests_pass :- 
    member1(5, [3, 4, 5, 7]),
    \+member1(10, [17, 225, 412, -33]),
    \+rest_list(7, [1, 2, 3, 4, 5], _),
    rest_list(3, [1, 2, 3, 4, 5, 3, 34], A), A = [3, 4, 5, 3, 34],
    append1([1, 2, 3], [5, 6, 7], B), B = [1, 2, 3, 5, 6, 7],
    zip([1, 2, 3], [a, b, c], C), zip([1, 2, 3, 4], [a, b, c], C), C = [1-a, 2-b, 3-c],
    zip([1, 2, 3, 4], [a, b, c, d, e, f], D), D = [1-a, 2-b, 3-c, 4-d],
    flatten([a, [b, c], [[d], [], [e]]], E), E = [a, b, c, d, e],
    flatten([1, 2, 3, 4], F), F = [1, 2, 3, 4].