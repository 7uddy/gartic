export module utils;
import <vector>;
import lobby;

export const std::unique_ptr<gartic::Lobby>* GetLobbyWithPlayer(const std::vector<std::unique_ptr<gartic::Lobby>>& lobbies, std::string_view username)
{
	std::string searchUsername{ username };
	for (auto& lobby : lobbies)
		if (lobby->IsInLobby(searchUsername))
			return &lobby;
	return nullptr;
}

export const std::unique_ptr<gartic::Lobby>* GetLobbyWithCode(const std::vector<std::unique_ptr<gartic::Lobby>>& lobbies, std::string_view lobbyCode)
{
	std::string searchCode{ lobbyCode };
	for (const auto& lobby : lobbies)
		if (lobby->CheckLobbyCode(searchCode))
			return &lobby;
	return nullptr;
}