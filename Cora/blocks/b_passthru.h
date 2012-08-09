#pragma once

DEFINE_BLOCK( b_passthru_1v1, 1, 1 )
{	
	BLOCK_WORK
	{
		auto nin = ninput(0);
		if(nin < 1) return false;
		auto ip1 = _$<int8>(0);
		auto op1 = $_<int8>(0);

    memcpy(op1, ip1, nin);

    consume(0, nin);
    produce(0, nin);

		return true;
	}
};