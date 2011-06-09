#ifndef GUILD_H
#define GUILD_H

#include <map>
#include <stdint.h>
using namespace std;

typedef uint64_t WorkLoad;
typedef void* Materials;

template <typename GuildName, typename Craft>
class Guild
    {
    private:
    protected:
        map< GuildName, Guild<Craft>* > subGuilds;
    public:
        virtual ~Guild()
            {
            //Il distruttore di map richiama i distruttori dei tipi contenuti, credo
            }
        void initiateSubGuild(GuildName guildName, Guild<Craft>* guild)
            {
            subGuilds[guildName] = guild;
            }
        void banishSubGuild(GuildName guildName)
            {
            subGuilds.erase(guildName);
            }
        virtual Craft* delegateWork(GuildName guildName, WorkLoad workLoad, Materials materials)
            {
            return subGuilds[guildName].delegateWork(guildName, workLoad, materials);
            }
    };

#endif // GUILD_H
