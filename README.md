j'ai realisé la premiere partie de la fonction expand "remplacement du variable par son contenu".
j'ai cree la nouvelle liste et je l'ai rempli chaque variable par son contenu.
j'ai realisé la fontion echo -n

/* c'est un essai de la deuxieme partie je l'ai mis ici pour ne pas la perdre, je voulais pas faire un push pour un code qui n'est pas fonctionnel

char	*expand_var(char *arr)
{
	char	str[ft_strlen(arr)];
	char	*value;
	int		i;
	int		j;

	i = 1;
	j = 0;
	value = malloc (sizeof(char) * (32767 + 1));
	value[32767] = '\0';
	while (arr[i])
		str[j++] = arr[i++];
	str[j] = '\0';
	printf("name of variable %s : \n", str);

	printf("toute la chaine %s : \n", str);
	// si cette chaine commence par $ et il ya un = dedans
	i = 1;
	while (arr[0] == '$' && arr[i] != '=' && arr[i])
		i++;
	if (arr[i] == '\0')
		value = strdup (expand(arr));
	else if (arr[i] == '=')
	{
		while (arr[i] != '"')
			i++;
		j = 0;
		while (arr[i] != '\0' && arr[i] != '"')
		{
			value[j] = arr[i];
			j++;
			i++;
		}
		value[j] = '\0';
	}
	printf("value of variable %s : \n", value);
	return(value);
}

