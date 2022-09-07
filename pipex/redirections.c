int open_file(vars)
{
    int fd;

    fd = open(vars->cmd[i_cmd], O_WRONLY, O_CREAT);
    if (fd < 0)
        return (-1);
    return (fd);
}

void    OUT_redir(t_vars *vars)
{
    int pid1;
    int pid2;
    int fd;
    int fd_pipe[2];

    if (pipe(fd_pipe) == -1)
        return ;
    pid1 = fork();
    if (pid1 < 0)
        return ;
    if (pid1 == 0)
    {
        dup2(fd_pipe[1], STDOUT_FILENO);
        close(fd_pipe[0]);
        close(fd_pipe[1]);
        find_cmd(vars);
    }
    fd = open_file(vars);
    pid2 = fork();
    if (pid2 < 0)
        return ;
    if (pid2 == 0)
    {
        dup2(fd_pipe[0], STDIN_FILENO);
        close(fd_pipe[1]);
        dup2(fd, fd_pipe[0]);
        close(fd_pipe[0]);
    }
    close(fd[0]);
    close(fd[1]);

}

void    IN_redir(t_vars *vars)
{
    find_cmd(vars);
    
}