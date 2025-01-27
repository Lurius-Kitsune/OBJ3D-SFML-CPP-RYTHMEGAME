#include "TextureManager.h"

TextureManager::TextureManager()
{
	defaultTexturePath = "Default";
	defaultTextureExtension = "png";
	defaultTexture = nullptr;
}

TextureManager::~TextureManager()
{
	delete defaultTexture;
}


void TextureManager::LoadDefaultTexture()
{
	const string& _finalPath = defaultTexturePath + "." + defaultTextureExtension;
	defaultTexture = new Texture();
	LoadTexture(*defaultTexture, _finalPath);
}

void TextureManager::LoadTexture(Texture& _texture, const string& _path, const IntRect& _rect)
{
	const string& _finalPath = "Assets/Textures/" + _path;
	if (!_texture.loadFromFile(_finalPath, false, _rect))
	{
		LOG(Error, "Cannot open file with the following path : \'" + _finalPath + "\' !");
		_texture = GetDefaultTexture();
	}
}

void TextureManager::SetTexture(Shape* _shape, const Texture* _texture)
{
	_shape->setTexture(_texture);
}

string TextureManager::GetExtensionNameByType(const TextureExtensionType& _textureType)
{
	const string _extensionNames[] =
	{
		"png",
		"jpg",
		"gif",
	};

	return _extensionNames[_textureType];
}


void TextureManager::Load(ShapeObject* _shapeObject, const string& _path, const TextureExtensionType& _textureType,
						  const IntRect& _rect,  const bool _isRepeated, const bool _smooth)
{
	Texture& _texture = _shapeObject->GetTexture();

	if (_path.empty())
	{
		LOG(Error, "Cannot open file with an empty path !");
		_texture = GetDefaultTexture();
	}

	// Init Texture
	const string _texturePath = _path + "." + GetExtensionNameByType(_textureType);
	LoadTexture(_texture, _texturePath, _rect);
	_texture.setRepeated(_isRepeated);
	_texture.setSmooth(_smooth);

	// Apply Texture
	SetTexture(_shapeObject->GetDrawable(), &_texture);
}

void TextureManager::Load(ShapeObject* _shapeObject, const string& _path, const IntRect& _rect,
						  const TextureExtensionType& _textureType, const bool _isRepeated, const bool _isSmooth)
{
	Load(_shapeObject, _path, _textureType, _rect, _isRepeated, _isSmooth);
}

void TextureManager::SetTextureRect(Shape* _shape, const Vector2i& _start, const Vector2i& _size)
{
	SetTextureRect(_shape, Rect(_start, _size));
}

void TextureManager::SetTextureRect(Shape* _shape, const IntRect& _rect)
{
	_shape->setTextureRect(_rect);
}