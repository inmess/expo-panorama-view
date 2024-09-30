import { NativeModulesProxy, EventEmitter, Subscription } from 'expo-modules-core';

// Import the native module. On web, it will be resolved to ExpoPanoramaView.web.ts
// and on native platforms to ExpoPanoramaView.ts
import ExpoPanoramaViewModule from './ExpoPanoramaViewModule';
import ExpoPanoramaView from './ExpoPanoramaView';
import { ChangeEventPayload, ExpoPanoramaViewProps } from './ExpoPanoramaView.types';

// Get the native constant value.
export const PI = ExpoPanoramaViewModule.PI;

export function hello(): string {
  return ExpoPanoramaViewModule.hello();
}

export async function setValueAsync(value: string) {
  return await ExpoPanoramaViewModule.setValueAsync(value);
}

const emitter = new EventEmitter(ExpoPanoramaViewModule ?? NativeModulesProxy.ExpoPanoramaView);

export function addChangeListener(listener: (event: ChangeEventPayload) => void): Subscription {
  return emitter.addListener<ChangeEventPayload>('onChange', listener);
}

export { ExpoPanoramaView, ExpoPanoramaViewProps, ChangeEventPayload };
