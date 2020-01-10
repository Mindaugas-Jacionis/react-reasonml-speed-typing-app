// bellow commented maybe pattern to apply for timer id
// type timerOption = option(Js.Global.intervalId);

// let doSomething = (timerIdO: timerOption) =>
//   switch (timerIdO) {
//   | Some(timerId) => Js.log(timerId)
//   | None => ()
//   };

// This could help to understanf options/maybes
// https://github.com/reasonml/reason-react/blob/master/docs/react-ref.md

type state = {
  time: int,
  timerId: Js.Global.intervalId,
};

type retainedProps = {shouldCount: bool};

type action =
  | SetTimer(Js.Global.intervalId)
  | Tick;

let component = ReasonReact.reducerComponentWithRetainedProps("Counter");

let make = (~onFinish, ~initialTime=60, ~shouldCount=true, _children) => {
  ...component,

  initialState: () => {
    time: initialTime,
    timerId: Js.Global.setInterval(() => (), 1000),
  },

  reducer: action =>
    switch (action) {
    | SetTimer(timerId) => (state => ReasonReact.Update({...state, timerId}))
    | Tick => (
        state => {
          let updatedTime = state.time - 1;

          if (updatedTime == 0) {
            Js.Global.clearInterval(state.timerId);
            onFinish();
          };

          ReasonReact.Update({...state, time: updatedTime});
        }
      )
    },

  didMount: ({send}) =>
    if (shouldCount) {
      let intervalId = Js.Global.setInterval(() => send(Tick), 1000);
      send(SetTimer(intervalId));
    },

  retainedProps: {
    shouldCount: shouldCount,
  },
  didUpdate: ({oldSelf, newSelf}) =>
    if (oldSelf.retainedProps.shouldCount !== newSelf.retainedProps.shouldCount
        && newSelf.retainedProps.shouldCount) {
      let intervalId = Js.Global.setInterval(() => newSelf.send(Tick), 1000);
      newSelf.send(SetTimer(intervalId));
    },

  willUnmount: ({state: {timerId}}) => Js.Global.clearInterval(timerId),

  render: ({state: {time}}) =>
    <div> {ReasonReact.string("Time left: " ++ string_of_int(time))} </div>,
};