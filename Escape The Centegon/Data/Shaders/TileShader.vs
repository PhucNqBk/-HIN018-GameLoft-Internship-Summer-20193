attribute 	vec3 	a_posL;
attribute 	vec2 	a_uv;

uniform 	mat4 	u_matMVP;
uniform 	mat4 	u_matWorld;
uniform 	float 	u_alpha;

uniform		float 	u_row;
uniform		float	u_col;
uniform		float 	u_curr_row;
uniform		float 	u_curr_col;

varying 	vec2 	v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_matMVP * posL;
	v_uv = vec2(a_uv.x*(1.0/u_col) + (1.0/u_col) * u_curr_col, a_uv.y*(1.0/u_row) + u_curr_row * (1.0/u_row));
}
   