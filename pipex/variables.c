
char    *get_cmd(t_vars *vars)
{
    int     i;
    char    *cmd;

    i = 0;
    while (vars->cmd[i_cmd + i])
        ++i;
    cmd = malloc(sizeof(char) * i + 1);
    i = 0;
    while (vars->cmd[i_cmd + i])
    {
        cmd[i] = vars->cmd[i_cmd + i];
        ++i;
    }
    return (cmd);
}

void variables(t_vars *vars)
{
    int     i;
    char    *cmd;

    i = 0;
    cmd = get_cmd(vars);
    if (get_env(cmd))
        printf("%s", cmd);
    else
        printf("variable does not exist\n");
    free(cmd);
}