#include <config.hpp>
#include <cmath>

#include <utility.hpp>
#include <objectmanager.hpp>
#include <objects/objects.hpp>
#include <objects/planet.hpp>

REGISTER_FACTORY( ObjectType::PLANET, Planet );

Planet::Planet( sf::String name, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Vector2f& velocity,
                float rotation, float rotational_velocity ) :
	Object( ObjectType::PLANET, name, size, position, velocity, rotation, rotational_velocity ),
	m_angle( 0 ) {
}

Planet::~Planet() {
}

void Planet::Update( float time ) {
	m_angle += GetVelocity().x * time;

	while( m_angle > 360 ) {
		m_angle -= 360;
	}

	while( m_angle < (-360) ) {
		m_angle += 360;
	}

	SetPosition( sf::Vector2f( static_cast<float>( cos( clean_angle( m_angle ) ) ) * GetVelocity().y,
	             static_cast<float>( sin( clean_angle( m_angle ) ) ) * GetVelocity().y ) );

	SetPosition( GetPosition() + m_anchor );

	SetRotation( GetRotation() + GetRotationalVelocity() * time );

	m_update_timer += time;
	if( m_update_timer > 10.0f ) {
		SetDirty();
		m_update_timer = 0.0f;
	}
}

void Planet::FillPartialPacket( const PacketPtr& packet ) {
	Object::FillPartialPacket( packet );
	(*packet) << m_angle;
}

void Planet::FillFullPacket( const PacketPtr& packet ) {
	Object::FillFullPacket( packet );
	(*packet) << m_angle << m_anchor.x << m_anchor.y;
}

void Planet::HandlePacket( const PacketPtr& /*packet*/ ) {

}

void Planet::SetOrbit( float velocity, float radius ) {
	SetVelocity( sf::Vector2f( velocity, radius ) );
}

void Planet::SetAngle( float angle ) {
	m_angle = angle;
}

void Planet::SetAnchor( float x, float y ) {
	m_anchor.x = x;
	m_anchor.y = y;
}
