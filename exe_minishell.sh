valgrind --leak-check=full \
--show-leak-kinds=all \
--track-origins=yes \
--suppressions=suppr.valgrind \
./minishell
