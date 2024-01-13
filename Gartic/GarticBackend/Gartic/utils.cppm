export module utils;
import <vector>;
import lobby;

export auto GetLobbyWithPlayer(const std::vector<std::unique_ptr<gartic::Lobby>>& lobbies, std::string_view username)
{
	std::string searchUsername{ username };
	for (const auto& lobby : lobbies)
		if (lobby->IsInLobby(searchUsername))
			return &lobby;
	const std::unique_ptr<gartic::Lobby> nullp;
	return &nullp;
}

export auto GetLobbyWithCode(const std::vector<std::unique_ptr<gartic::Lobby>>& lobbies, std::string_view lobbyCode)
{
	std::string searchCode{ lobbyCode };
	for (const auto& lobby : lobbies)
		if (lobby->CheckLobbyCode(searchCode))
			return &lobby;
	const std::unique_ptr<gartic::Lobby> nullp;
	return &nullp;

}