/*
Stupidity Overload
Copyright (C) 2017 Gaïda Mohamed Alaa Eddine <med.gaida@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

class EventHandler {
public:
  using EventCallback = std::function<void(SDL_Event const&)>;

  void register(SDL_EventType type, EventCallback callback) {
    _registeredCallbacks[type].push_back(callback);
  }

  void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      for (auto& cb : _registeredCallbacks[event.type]) {
        cb(event);
      }
    }
  }

private:
  std::map<SDL_EventType, std::vector<EventCallback>> _registeredCallbacks;
};

class GameManager {
public:

  void registerWithEventHandler(EventHandler& handler) {
    handler.register(SDL_KEYUP, [this](SDL_Event const& event){
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        Quit();
      }
    });
    handler.register(SDL_QUIT, [this](SDL_Event const& event){
      Quit();
    });
  }

}