#pragma once

namespace cs2
{
	class c_player_weapon_services
	{
	public:
		std::pair<int, cs2::c_base_player_weapon*> get_my_weapons()
		{
			// @NOTE: num weapons is at + 0x0, data is at + 0x8 (https://www.unknowncheats.me/forum/3711351-post132.html)
			return
			{
				m_memory.read_t<int>(this + m_offsets.get_my_weapons()),
				m_memory.read_t<cs2::c_base_player_weapon*>(this + m_offsets.get_my_weapons() + 0x08)
			};
		}

		cs2::c_base_player_weapon* get_active_weapon()
		{
			const auto entity_list = m_cs2.get_entity_list();
			if (!entity_list)
				return nullptr;

			const auto handle = m_memory.read_t<int>(this + m_offsets.get_active_weapon());
			if (handle == -1)
				return nullptr;

			return entity_list->get<cs2::c_base_player_weapon*>(handle & 0x7fff);
		}
	};
}