#pragma once

#define GROUP_CHAR_ARR_LEN 20
#define USER_CHAR_ARR_LEN 20
#define MSG_CHAR_ARR_LEN 100

typedef struct record {
	int id;
	char group[GROUP_CHAR_ARR_LEN];
	char user[ USER_CHAR_ARR_LEN ];
	char msg[  MSG_CHAR_ARR_LEN  ];
	long timestamp;
} record;

int RecordCompare(record* r1,record* r2);
void RecordPrint(record* r);
record* Record(
	int id,
	char group[GROUP_CHAR_ARR_LEN],
	char user[ USER_CHAR_ARR_LEN ],
	char msg[  MSG_CHAR_ARR_LEN  ],
	long timestamp
	);

void initialize(record* r,int id,char group[GROUP_CHAR_ARR_LEN],char user[USER_CHAR_ARR_LEN],char msg[MSG_CHAR_ARR_LEN],long timestamp);
