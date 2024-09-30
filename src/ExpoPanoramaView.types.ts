import { ViewProps } from 'react-native'; 

export type ChangeEventPayload = {
    value: string;
};

export type PlayStateEventPayload = {
    state: "playing" | "paused" | "completed";
};

export type ProgressEventPayload = {
    position: number;
};

export type LogEventPayload = {
    message: string;
};

export type ExpoPanoramaViewProps = {
    url: string;
    onPlayStateChanged?: (event: { nativeEvent: PlayStateEventPayload }) => void;
    onProgress?: (event: { nativeEvent: ProgressEventPayload }) => void;
    isPlaying?: boolean;
    onLog?: (event: { nativeEvent: LogEventPayload }) => void;
} & ViewProps;
