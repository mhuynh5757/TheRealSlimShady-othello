The improvements I made to the AI were rewriting the AI completely in C++ instead of Java, improving heuristic
scores, and removing minimax in favor of negascout. Negascout is better than minimax because it simplifies searching
and uses alpha-beta pruning. Java did not work because the tournament needed a completely separate program to run.