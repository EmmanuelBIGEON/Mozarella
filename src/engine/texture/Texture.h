#pragma Once

#include <string>

class Texture
{
public:
	Texture();
    virtual ~Texture();
    
	// Renvoie forcément une texture, permettant de ne pas à avoir à vérifier son existence.
	static Texture* Load(const std::string& filePath);

	void Bind(unsigned int slot);

	unsigned int GetID();

private:
	unsigned int _ID;
	unsigned char* _data = nullptr;
};