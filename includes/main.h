/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 01:28:47 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/01 14:46:19 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

# define START_CMD "##start\n"
# define END_CMD "##end\n"
# define LEN ft_strlen(env->graph[move[1]].name)
# define ANT_NLEN 12
# define BUFF_READ 65536
# define BUFF_WRITE 65536

typedef struct s_queue	t_queue;

struct					s_queue
{
	t_queue				*next;
	unsigned int		index;
	int					pad;
};

typedef struct			s_room
{
	char				*name;
	char				type;
	char				pad[7];
}						t_room;

typedef struct			s_path
{
	int					*path;
	int					*ants;
	unsigned int		ammos;
	unsigned int		len;
}						t_path;

typedef struct			s_env
{
	char				**matrix;
	int					**path_moves;
	char				*file;
	t_room				*graph;
	t_path				*paths;
	int					*parent;
	bool				*arriveds;
	bool				*visited;
	long long int		nb_ants;
	int					start;
	int					end;
	int					file_len;
	unsigned int		nb_rooms;
	unsigned int		nb_paths;
	unsigned int		max_flow;
	unsigned int		count;
	unsigned int		pipes_start;
}						t_env;

/*
** Parsing
*/
char					*read_fd_zero(int *len);
t_room					*parsing(t_env *env);
void					next_line(char *file, unsigned int *i);
unsigned int			count_rooms(char *file, unsigned int *j);
t_room					*make_graph(t_env *env);
bool					room_err_cases(t_env *env);

/*
** Micro state-machine
*/
int						load_line(t_env *env, char s, unsigned int i, int room);
char					get_line_state(char *line, bool flush);
bool					is_room(char *line);
bool					is_pipe(char *line);
bool					is_comment(char *line);
bool					is_cmd(char *line);

/*
** Matrice d'adjacence
*/
int						make_matrix(t_env *env, unsigned int i);
int						find_from(t_env *env, char *line);
int						find_to(t_env *env, char *line);

/*
** Resolution
*/
unsigned int			edmond_karp(t_env *env, bool up);
bool					breadth_first_search(t_env *env, int s, int e, bool up);
t_path					*allocate_paths(t_env *env);
bool					is_disjoint(t_env *env);
int						sort_paths(t_env *env);
int						load_ammos(t_env *env);

/*
** Output buffering
*/
int						crossing(t_env *env);
int						output_buffer(t_env *env, int move[2], bool nl, bool f);
bool					*space(void);
int						start_end(t_env *env);

/*
** Lists
*/
t_queue					*lm_lstnew(int room);
int						lm_lstdel(t_queue *queue);
int						lm_lst_pop(t_queue **lst);
int						lm_lst_push(t_queue **lst, int index);

/*
** Free
*/
t_room					*free_graph(t_env *env);
t_env					*free_env(t_env *env);
char					**free_matrix(char **matrix, unsigned int n);

#endif
