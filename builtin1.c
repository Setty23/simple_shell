#include "shell.h"

/**
 * my_exit - custom exit handler function.
 * @info: Pointer to a structure containing relevant information.
 *
 *  Return: 0: If the exit argument is not provided
 *          -2: If the exit argument is successfully converted.
 */
int my_exit(info_t *info)
{
	int check;

	if (info->argv[1])  /* If  an exit arguement exists*/
	{
		check = my_atoi(info->argv[1]);
		if (check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_errputs(info->argv[1]);
			/*_eputchar('\n'); */
			write_stdout("\n");
			return (1);
		}
		info->err_num = check;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - custom changes current directory handler function.
 * @info: Pointer to a structure containing relevant information.
 *
 *  Return: Always 0
 */
int my_cd(info_t *info)
{
	char *x;
	char *dir;
	char buffer[1024];
	int chdir_ret;

	x = getcwd(buffer, 1024);
	if (!x)
		_puts("TODO: >>getcwd failure msg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should it be? */
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (my_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should it be? */
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_errputs(info->argv[1]), _errputchar('\n');
	}
	return (0);
}

/**
 * my_help - custom changes cirrent directory function.
 * @info: Structure that has potential maintains
 * constant function.
 *  Return: Always 0
 */
int my_help(info_t *info)
{
	char **arg;

	arg = info->argv;
	_puts(" Function not yet implemented \n");
	if (0)
		_puts(*arg);
	return (0);
}

/**
 * my_history - functions displays history list, .
 * @inf: Structure containing potential arguments. maintains
 *        constant function prototype.
 *  Return: Always 0
 */
int my_history(info_t *inf)
{
	print_list(inf->history);
	return (0);
}
